import os
import shutil

# 定义根目录和目标子目录
base_dir = '/home/dell/zyworkspace/unichecker/Experiments/svcomp2022'
# target_dir = os.path.join(base_dir, 'Idv-races')
# target_dir = os.path.join(base_dir, 'pthread')
target_dir = os.path.join(base_dir, 'goblint-regression')

# 扫描目标目录下所有以 .c 结尾的文件
for filename in os.listdir(target_dir):
    if filename.endswith('.c'):
        file_path = os.path.join(target_dir, filename)
        # 获取不带.c后缀的文件名
        folder_name = filename[:-2]
        folder_path = os.path.join(target_dir, folder_name)
        # 创建新文件夹（如果不存在）
        os.makedirs(folder_path, exist_ok=True)
        # 移动文件到新文件夹
        shutil.move(file_path, os.path.join(folder_path, filename))

print('批处理完成。')