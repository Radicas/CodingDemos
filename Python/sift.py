import pandas as pd
import numpy as np
import shutil
import os

fd = "/Users/zhupeng/Downloads/公差分析报备名单（100个）20210222(2)(1).xlsx"
pdf_path = "/Users/zhupeng/Downloads/pdf/"
src_path = "/Users/zhupeng/Downloads/pdf/"
dst_path = "/Users/zhupeng/Downloads/pdf_tartgets/"

df = pd.read_excel(fd)
id_df = df["id"]
id = set(id_df)

def move_file(src_path, dst_path, file):

    print ('from: %s', src_path)
    print ('to: %s', dst_path)
    try:
        f_src = os.path.join(src_path, file)
        f_dst = os.path.join(dst_path, file)
        shutil.move(f_src, f_dst)
    except Exception as e:
        print ('move_file ERROR: ',e)

for target_a in id:
    for target_b in os.listdir(pdf_path):
        target_c = str(target_b).strip("简历ID：")
        target_d = str(target_c).strip(".pdf")
        if(str(target_a)==target_d):
            move_file(src_path, dst_path, str(target_b))
        else:
            pass

