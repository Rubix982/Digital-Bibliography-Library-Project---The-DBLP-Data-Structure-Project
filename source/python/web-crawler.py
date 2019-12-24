import requests, sys

sys.path.append("/home/saif/Desktop/Folders/Projects/Data Structures - Project/source/python/dblp-0.1.0" );

import dblp
from bs4 import BeautifulSoup
import PyPDF2

# search_string = input('Enter author name for search: ')
# search_results = dblp.search(search_string)

# if(search_results.empty):
#     print("No results...\nExtting...")
#     exit(1)

# for index, value in search_results.iterrows():
#     print(f"{index}): {value.Title}\n")

# option = int(input('Enter index of the record to get data: '))
# record = search_results.loc[option]

# request = requests.get(record.Link)

# html_soup = BeautifulSoup(request.text, 'html.parser')
# download_link = html_soup.find('a', class_='c-pdf-download__link')
# get_pdf = download_link.get('href')
# request = requests.get("https://" + get_pdf[2:])

# with open("".join("PDF.pdf"), "wb" ) as pdf_file:
#     pdf_file.write(request.content)

pdfFileObj = open('PDF.pdf', 'rb')
pdfReader = PyPDF2.PdfFileReader(pdfFileObj)
numOfPages = pdfReader.numPages

with open("sample.txt", "w") as txt_file:
    for i in range(numOfPages):
        txt_file.write(pdfReader.getPage(i).extractText())
        txt_file.write(' \n')