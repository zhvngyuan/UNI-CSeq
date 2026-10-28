import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns

# 读取数据
df = pd.read_csv('all_results.csv')

# 验证时间对比图
plt.figure(figsize=(12, 8))

# 按工具和展开参数分组计算平均验证时间
time_by_tool = df.groupby(['tool', 'unwind'])['time'].mean().reset_index()
time_by_tool_pivot = time_by_tool.pivot(index='unwind', columns='tool', values='time')

# 为CBMC在不同展开参数下添加数据点
cbmc_data = time_by_tool[time_by_tool['tool'] == 'CBMC']
cpa_avg_time = df[df['tool'] == 'CPAchecker']['time'].mean()

# 绘制CBMC在不同展开参数下的时间曲线
ax = sns.lineplot(data=cbmc_data, x='unwind', y='time', marker='o', markersize=10, linewidth=2, color='blue', label='CBMC')

# 添加CPAchecker的水平线
plt.axhline(y=cpa_avg_time, color='red', linestyle='--', linewidth=2, label='CPAchecker (平均)')

plt.title('CBMC与CPAchecker验证时间对比', fontsize=15)
plt.xlabel('CBMC展开参数', fontsize=12)
plt.ylabel('平均验证时间 (秒)', fontsize=12)
plt.legend(fontsize=12)
plt.grid(True, linestyle='--', alpha=0.7)

plt.tight_layout()
plt.savefig('verification_time_comparison.png', dpi=300)
plt.show()