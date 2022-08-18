from curses.ascii import isalpha


data = input()
result = []
value = 0

#문자 하나씩 확인
for x in data:
    if x.isalpha():
        result.append(x)
    else:
        value += int(x)

#오름차순 정렬
result.sort()

#숫자 있으면 맨 뒤에 결과 값 넣기
if value != 0:
    result.append(str(value))
    
#리스트를 스트링으로 출력
print(''.join(result))