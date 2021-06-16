from pyquery import PyQuery as pq
from pyquery.pyquery import PyQuery


class Analyzer:
    
    def __init__(self, html) -> None:
        self.html = html
        self.doc = pq(self.html)
        self.data: dict = {}
        # 
        self.mode = 0
        self.tables: PyQuery = ...

    def analyze(self):
        self.get_tables()
        self.analyze_profile(self.tables.eq(0))
        # self.analyze_recent(self.tables.eq(2))
        self.analyze_work_experiences(self.tables.eq(5))
        # eq(3)
        # eq(4)

    def get_tables(self):
        top_level_table = self.doc('body').children('table').eq(1)
        name = top_level_table.find("strong").text()
        if not name:
            top_level_table = self.doc('body').children('table').eq(2)
        self.tables = top_level_table.children('tbody > tr > td').eq(0).children('table')
        if not self.tables:
            self.tables = top_level_table.children('tr > td').eq(0).children('table').eq(0).children('tbody > tr > td > table')
            if not self.tables:
                self.tables = top_level_table.children('tbody > tr > td').eq(0).children('table').eq(1).children('tbody > tr > td').eq(0).children('table')

    def analyze_profile(self, profile_table: PyQuery):
        rows = profile_table.children('tbody > tr > td').eq(1).children('table')
        self.data['name'] = rows.eq(0).find('strong').text()

        tel_mail = rows.eq(1).children('tbody > tr > td')
        self.data['tel'] = tel_mail.eq(0).find('td').eq(1).text()
        self.data['mail'] = tel_mail.eq(1).find('td').eq(1).text()
        # print(len(rows))

    def get_title_from_table(self, table: PyQuery):
        return table.children('tbody > tr > td').eq(0).text()

    def get_work_experience_tables(self, work_experiences_table: PyQuery) -> PyQuery:
        table_wrapper_tr = work_experiences_table.children('tbody > tr').eq(1).children('td > table > tr')
        tables = [tr.children('td > table') for tr in table_wrapper_tr.items()]
        return PyQuery(tables)
    
    def analyze_work_experiences(self, work_experience_area_table: PyQuery):
        tables = self.get_work_experience_tables(work_experience_area_table)
        for table in tables.eq(0).items():
            rows = table.children('tbody > tr')
            position = rows.eq(0).children('td').eq(1).text()
            company_name = rows.eq(1).find('span').eq(0).text()
            self.data["company"] = company_name
            self.data['position'] = "".join(position.split()) 
        title = work_experience_area_table.children('tbody > tr').eq(0).children('td').text()       
        if title!='工作经验':
            tables = self.get_work_experience_tables(self.tables.eq(3))
            for table in tables.eq(0).items():
                rows = table.children('tbody > tr')
                position = rows.eq(0).children('td').eq(1).text()
                company_name = rows.eq(1).find('span').eq(0).text()
                self.data["company"] = company_name
                self.data['position'] = "".join(position.split()) 
            title = self.tables.eq(3).children('tbody > tr').eq(0).children('td').text()
            if title != '工作经验':
                tables = self.get_work_experience_tables(self.tables.eq(4))
                for table in tables.eq(0).items():
                    rows = table.children('tbody > tr')
                    position = rows.eq(0).children('td').eq(1).text()
                    company_name = rows.eq(1).find('span').eq(0).text()
                    self.data["company"] = company_name
                    self.data['position'] = "".join(position.split()) 


def main():
    file = "简历/resume.html"
    with open(file, encoding='gb18030') as f:
        ana = Analyzer(f.read())
        ana.analyze()
        print(ana.data)


if __name__ == "__main__":
    main()
