import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns
import matplotlib.font_manager as fm

# 读取数据
df = pd.read_csv('all_results.csv')

# 正确性与效率权衡图
# 计算每种策略的平均验证时间
cbmc_avg_times = parallel_df.groupby('unwind')['CBMC_time'].mean()
cpa_avg_time = parallel_df['CPAchecker_time'].mean()
parallel_avg_times = parallel_df.groupby('unwind')['Parallel_time'].mean()

# 结合并行验证策略的时间收益分析
# 计算各种策略下的平均时间
time_comparison = pd.DataFrame({
    'CBMC': cbmc_avg_times.values,
    'CPAchecker': [cpa_avg_time] * len(cbmc_avg_times),
    'Parallel': parallel_avg_times.values
}, index=cbmc_avg_times.index)

# 计算并行策略相对于单独使用CPAchecker的时间节省
time_comparison['Time_Saving'] = (time_comparison['CPAchecker'] - time_comparison['Parallel']) / time_comparison['CPAchecker'] * 100

# 绘制时间节省百分比图
plt.figure(figsize=(10, 6))
ax = sns.barplot(x=time_comparison.index, y=time_comparison['Time_Saving'], palette='YlGnBu')

plt.title('并行策略相对于CPAchecker的时间节省', fontsize=15)
plt.xlabel('CBMC展开参数', fontsize=12)
plt.ylabel('时间节省百分比 (%)', fontsize=12)
plt.grid(axis='y', linestyle='--', alpha=0.7)

# 添加数据标签
for i, pct in enumerate(time_comparison['Time_Saving']):
    sign = '+' if pct > 0 else ''
    ax.text(i, pct + (5 if pct > 0 else -15), f'{sign}{pct:.1f}%', ha='center', fontsize=10)

plt.tight_layout()
plt.savefig('time_saving_analysis.png', dpi=300)
plt.show()