#DFS 메소드
def dfs(graph, v, visited):
    #현재 노드 방문
    visited[v] = True
    print(v, end=' ')
    #현재 노드와 연결된거 재귀적 방문
    for i in graph[v]:
        if not visited[i]:
            dfs(graph, i, visited)

#노드 연결된 정보
graph = [
    [],
    [2, 3, 8],
    [1, 7],
    [1, 4, 5],
    [3, 5],
    [3, 4],
    [7],
    [2, 6, 8],
    [1, 7]
]

#방문 정보
visited = [False] * 9

#dfs 함수 호출
dfs(graph, 1, visited)