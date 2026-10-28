#!/usr/bin/env python
# -*- coding: utf-8 -*-
"""Comment a live assert (or macro call that expands to assert) at a 1-based line.

Usage:
    python icbmc_comment_assert.py <c_file> <line_number>

Exit 0 on success, 1 if the line has no live assert/call or is already commented.
Prints a one-line description of the edit.
"""
from __future__ import print_function

import os
import re
import sys

MACRO_CALL_RE = re.compile(
    r"\b(pca_isa_probe|i8xx_tco_release|wdtpci_release)\s*\("
)


def split_nl(text):
    if text.endswith("\r\n"):
        return text[:-2], "\r\n"
    if text.endswith("\n"):
        return text[:-1], "\n"
    if text.endswith("\r"):
        return text[:-1], "\r"
    return text, ""


def live_code_prefix(line):
    """Return line with // comments and trailing newline stripped for inspection."""
    body, _ = split_nl(line)
    out = []
    i = 0
    in_str = False
    while i < len(body):
        ch = body[i]
        if in_str:
            out.append(ch)
            if ch == "\\" and i + 1 < len(body):
                out.append(body[i + 1])
                i += 2
                continue
            if ch == '"':
                in_str = False
            i += 1
            continue
        if ch == '"':
            in_str = True
            out.append(ch)
            i += 1
            continue
        if body[i : i + 2] == "//":
            break
        out.append(ch)
        i += 1
    return "".join(out)


def find_assert_span(code):
    """Return (start, end) of first live assert(...) in code, or None."""
    i = 0
    n = len(code)
    while i < n:
        j = code.find("assert", i)
        if j < 0:
            return None
        prev = code[j - 1] if j > 0 else ""
        if prev.isalnum() or prev == "_":
            i = j + 6
            continue
        k = j + 6
        while k < n and code[k] in " \t":
            k += 1
        if k >= n or code[k] != "(":
            i = j + 6
            continue
        depth = 0
        p = k
        while p < n:
            if code[p] == "(":
                depth += 1
            elif code[p] == ")":
                depth -= 1
                if depth == 0:
                    return (j, p + 1)
            p += 1
        return None
    return None


def comment_assert_in_line(line):
    body, nl = split_nl(line)
    live = live_code_prefix(line)
    span = find_assert_span(live)
    if span is None:
        return None
    start, end = span
    assert_txt = body[start:end]
    tail = body[end:]
    # Keep macro line-continuation outside the comment.
    cont = ""
    stripped_tail = tail.rstrip()
    if stripped_tail.endswith("\\"):
        # tail is like "; \" or "; \\"
        before_bs = stripped_tail[: stripped_tail.rfind("\\")].rstrip()
        cont = tail[len(before_bs) :]  # includes spaces + backslash (+ leftover)
        # Recompute: body = prefix + assert + after_assert
        after = body[end:]
        bs = after.rfind("\\")
        if bs >= 0:
            mid = after[:bs].rstrip()
            cont = after[len(mid) :]
            new_body = body[:start] + "/*" + assert_txt + "*/" + mid + cont
            return new_body + nl, assert_txt
    new_body = body[:start] + "//" + assert_txt + tail
    return new_body + nl, assert_txt


def comment_macro_call_in_line(line):
    body, nl = split_nl(line)
    live = live_code_prefix(line)
    m = MACRO_CALL_RE.search(live)
    if not m:
        return None
    start = m.start()
    # Find end of call: matching paren then optional semicolon
    p = m.end() - 1
    depth = 0
    while p < len(live):
        if live[p] == "(":
            depth += 1
        elif live[p] == ")":
            depth -= 1
            if depth == 0:
                p += 1
                break
        p += 1
    if p < len(live) and live[p] == ";":
        p += 1
    call_txt = body[start:p]
    after = body[p:]
    if after.rstrip().endswith("\\"):
        new_body = body[:start] + "/*" + call_txt + "*/" + after
    else:
        new_body = body[:start] + "//" + call_txt + after
    return new_body + nl, call_txt


def try_comment_line(line):
    live = live_code_prefix(line).strip()
    if not live:
        return None, "already_commented_or_empty"
    edited = comment_assert_in_line(line)
    if edited is not None:
        return edited[0], "assert:" + edited[1]
    edited = comment_macro_call_in_line(line)
    if edited is not None:
        return edited[0], "call:" + edited[1]
    return None, "not_found"


def main(argv):
    if len(argv) != 3:
        print("Usage: icbmc_comment_assert.py <c_file> <line_number>", file=sys.stderr)
        return 2
    path = argv[1]
    try:
        lineno = int(argv[2])
    except ValueError:
        print("error: line number must be an integer", file=sys.stderr)
        return 2
    if not os.path.isfile(path):
        print("error: file not found: %s" % path, file=sys.stderr)
        return 1
    with open(path, "rb") as f:
        raw = f.read()
    try:
        text = raw.decode("utf-8")
    except UnicodeDecodeError:
        text = raw.decode("latin-1")
    lines = text.splitlines(True)
    if lineno < 1 or lineno > len(lines):
        print("error: line %d out of range (file has %d lines)" % (lineno, len(lines)), file=sys.stderr)
        return 1

    candidates = [lineno]
    # CBMC sometimes reports the if-line immediately above assert(0).
    if lineno < len(lines):
        candidates.append(lineno + 1)

    edited_idx = None
    desc = None
    new_line = None
    for cand in candidates:
        idx = cand - 1
        result, kind = try_comment_line(lines[idx])
        if result is not None:
            edited_idx = idx
            desc = kind
            new_line = result
            break
        if kind == "already_commented_or_empty" and cand == lineno:
            print("error: line %d is empty or already commented" % cand, file=sys.stderr)
            return 1

    if new_line is None:
        snippet = lines[lineno - 1].rstrip("\r\n")
        print("error: no live assert/macro call at line %d: %s" % (lineno, snippet), file=sys.stderr)
        return 1

    lines[edited_idx] = new_line
    with open(path, "wb") as f:
        f.write("".join(lines).encode("utf-8"))
    print("commented line %d (%s)" % (edited_idx + 1, desc))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
