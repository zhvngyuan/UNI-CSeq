import pandas as pd

cbmc_cpachecker_csv = "all_results.csv"
unicseq_csv = "unicseq_results.csv"

df1 = pd.read_csv(cbmc_cpachecker_csv)
df2 = pd.read_csv(unicseq_csv)
df = pd.concat([df1, df2], ignore_index=True)
# 保证case名唯一化易对比
df['case_id'] = df['benchmark'] + '/' + df['case']
df.to_csv("all_results_with_unicseq.csv", index=False)