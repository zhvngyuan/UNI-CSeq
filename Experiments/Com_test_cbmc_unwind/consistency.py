import pandas as pd
import matplotlib.pyplot as plt

# 读取数据
df = pd.read_csv("all_results_with_unicseq.csv")
df['unwind'] = df['unwind'].astype(str).str.strip()

df_cbmc2 = df[(df['tool'] == 'CBMC') & (df['unwind'] == '2.0')][['case', 'result']].rename(columns={'result': 'cbmc2_result'})
df_cpachecker = df[df['tool'] == 'CPAchecker'][['case', 'result']].rename(columns={'result': 'cpachecker_result'})
df_merge = pd.merge(df_cbmc2, df_cpachecker, on='case', how='inner')

df_merge['Consistent'] = df_merge['cbmc2_result'] == df_merge['cpachecker_result']
df_merge['Consistency'] = df_merge['Consistent'].map({True: 'Consistent', False: 'Inconsistent'})
summary = df_merge.groupby(['Consistency', 'cpachecker_result']).size().unstack(fill_value=0)

# 指定自定义颜色
custom_colors = ['#2C78BB', '#FF8C1A']  # 蓝色，橙黄色

ax = summary.T.plot(
    kind='bar',
    stacked=True,
    color=custom_colors,
    width=0.2,            # 控制条形宽度
    figsize=(4, 4)
)

# ax = plt.gca()  # 获取当前坐标轴
# ax.spines['top'].set_visible(False)    # 取消顶部横线
# ax.spines['right'].set_visible(False)  # 取消右侧竖线

# plt.xlabel('CPAchecker Result')
plt.xlabel('')
plt.ylabel('Number of Cases')
# plt.title('Result Consistency between CBMC (u=2) and CPAchecker')
plt.legend(title='Consistency')
plt.tight_layout()

# 设置横轴标签为水平
ax.set_xticklabels(ax.get_xticklabels(), rotation=0)

plt.tight_layout()
plt.subplots_adjust(bottom=0.13)  # 适当调整下边距，具体数值可微调

plt.savefig('cbmc_cpachecker_consistency_en_color.png', dpi=300)
plt.show()
