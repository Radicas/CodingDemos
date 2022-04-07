import re 
import numpy as np
import pandas as pd
from ctypes import sizeof
from pickle import FALSE

path = "/Users/radica/Downloads/copy.xlsx"       # 原文件地址
new_path = "/Users/radica/Downloads/target.xlsx" # 目标文件地址

df = pd.read_excel(path)     # 表格数据读进dataframe
temp_list = []               # 临时list，存储目标数据
for c in range(df.shape[1]): # 遍历列
    col_name = df.columns[c] # 列名
    data = set(df[col_name]) # 去重
    for target in data:
        if("@" in str(target)):
            words = re.findall(r'([a-zA-Z0-9_.+-]+@[a-pr-zA-PRZ0-9-]+\.[a-zA-Z0-9-.]+)', target) # 正则获取邮箱
            for w in words:
                temp_list.append(w)

sheet = df                                     # 创建sheet
writer = pd.ExcelWriter(new_path)              # 创建writer
sheet.to_excel(writer, "emails", FALSE)        # 表格插入sheet

temp_dict = {}                                 # 初始化字典
temp_dict["email"] = temp_list                 # 数据写入字典
new_df = pd.DataFrame.from_dict(temp_dict)     # 字典转换成dataframe
new_df.to_excel(new_path, sheet_name="sheet1") # 数据写入表格