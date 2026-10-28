import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

TIME_LIMIT = 900.0

def normalize_runtime(t):
    try:
        t = float(t)
    except (TypeError, ValueError):
        return np.nan
    if np.isnan(t) or t <= 0:
        return np.nan
    if t >= TIME_LIMIT:
        return TIME_LIMIT
    return t

df = pd.read_csv('all_results.csv')

# 预处理：有效墙钟保留；>=900s 视为超时计 900；UNKNOWN/TIMEOUT 一并纳入
df['tool'] = df['tool'].astype(str).str.strip()
df['unwind'] = df['unwind'].astype(str).str.strip()
df['time'] = df['time'].apply(normalize_runtime)
df = df.dropna(subset=['time'])

def group_label(row):
    if row['tool'] == 'CBMC':
        return f'CBMC-u{str(int(float(row["unwind"])))}'
    else:
        return 'CPAchecker'

df['group'] = df.apply(group_label, axis=1)

print("所有分组标签：", df['group'].unique())
print(df.groupby('group').size())

order = [f'CBMC-u{u}' for u in ['2', '4', '8', '16', '32']] + ['CPAchecker']

data = []
labels = []
for g in order:
    values = df[df['group'] == g]['time']
    if len(values) == 0:
        print(f"Warning: group {g} has no data, will be skipped.")
        continue
    data.append(values.values)
    labels.append(g)

plt.figure(figsize=(6, 4))

boxprops = dict(linewidth=1, color='k')
medianprops = dict(linewidth=1.5, color='orange')
whiskerprops = dict(linewidth=1, color='k')
capprops = dict(linewidth=1, color='k')

# 这里先把默认离群点隐藏，后面自己画
flierprops = dict(marker='o', markersize=0)

bp = plt.boxplot(
    data,
    labels=labels,
    patch_artist=False,
    showmeans=False,
    showfliers=False,   # 关键：关闭默认离群点
    boxprops=boxprops,
    medianprops=medianprops,
    whiskerprops=whiskerprops,
    capprops=capprops,
    flierprops=flierprops,
    widths=0.3
)

# -----------------------------
# 手动计算离群点，并添加“光晕”
# -----------------------------
for i, values in enumerate(data, start=1):
    values = np.asarray(values)

    q1 = np.percentile(values, 25)
    q3 = np.percentile(values, 75)
    iqr = q3 - q1
    lower = q1 - 1.5 * iqr
    upper = q3 + 1.5 * iqr

    fliers = values[(values < lower) | (values > upper)]

    if len(fliers) == 0:
        continue

    # 为避免点完全重叠，可以加一点轻微水平抖动
    x_center = i
    jitter = np.random.uniform(-0.005, 0.005, size=len(fliers))
    x = x_center + jitter
    # x = np.full(len(fliers), i)

    # 第1层：光晕层（更大、更透明、浅蓝）
    plt.scatter(
        x, fliers,
        s=70,                  # 光晕大小
        facecolors='#7DB7FF',  # 浅蓝
        edgecolors='none',
        alpha=0.1,
        zorder=2
    )

    # 第2层：主体空心圆
    plt.scatter(
        x, fliers,
        s=26,
        facecolors='none',
        edgecolors='#2C84E8',
        linewidths=0.7,
        alpha=0.95,
        zorder=3
    )

plt.yscale('log')

ax = plt.gca()
ax.spines['top'].set_visible(False)
ax.spines['right'].set_visible(False)

plt.ylabel('Runtime (Wall time, s)')
ax.set_xlabel("Backend Configuration")
plt.tight_layout()
plt.savefig('runtime_boxplot_style.png', dpi=300)
plt.show()