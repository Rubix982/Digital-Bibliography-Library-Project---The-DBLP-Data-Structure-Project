import dblp, requests

search_string = input('Enter author name for search: ')
search_results = dblp.search(search_string)
if(search_results.empty):
    print("No results...\nExitting...")
    exit(1)
print(f'Index\tType\tAuthor Names\tYear')
for index, val in search_results.iterrows():
    print(f'{index}\t{val.Type}\t{val.Authors}\t{val.Title}\t{val.Year}')
print('\n\t\t---------------------------------\n')
option = int(input('Enter index of the record to get data: '))
record = search_results.loc[option]

request = requests.get(record.Link)
print(request.status_code)
print(request.text)
