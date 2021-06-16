import os
import pandas as pd
from glob import glob
from analyzer import Analyzer

os.chdir('data')
data = []
files = list(glob("*.html"))
# files = ['105resume.html']
for file in files:
    try:
        with open(file, encoding="gb18030") as f:
            ana = Analyzer(f.read())
            ana.analyze()
            data.append(ana.data)
            ana.data['file'] = file
            print(file, ana.data)
    except Exception as e:
        print("%s 解析失败" % file)
os.chdir('..')
pd.DataFrame(data).to_csv('output.csv', index=False)
