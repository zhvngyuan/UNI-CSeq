import json

# 读取ground_truth.json
with open('ground_truth.json', 'r', encoding='utf-8') as f:
    gtdata = json.load(f)

# ground_truth信息在'programs'字段下
programs = gtdata['programs']

# 构造新字典
REAL_GROUND_TRUTH = {}
for k, v in programs.items():
    # 提取每个程序的断言ground_truth
    REAL_GROUND_TRUTH[k] = v['ground_truth'].upper()  # 转成大写，保证一致性

# 输出为json文件
with open('real_ground_truth.json', 'w', encoding='utf-8') as f:
    json.dump(REAL_GROUND_TRUTH, f, indent=2, ensure_ascii=False)

# 也可以直接输出为Python代码格式
print("REAL_GROUND_TRUTH = {")
for k, v in REAL_GROUND_TRUTH.items():
    print(f'    "{k}": "{v}",')
print("}")