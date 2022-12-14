all_c="_abcdefghijz"

def choose_v(T,L):
	v = list(T)[0]
	lv = L[v]

	for i in range(len(T)):
		v_now = list(T)[i]
		lv_now = L[v_now]

		if lv_now < lv:
			v = v_now
			lv = lv_now
	return v,lv


def make_graph():
	info = [['a' ,'b', 4], ['a' ,'e', 1], ['a' ,'h', 6], ['b' ,'e', 6], ['e' ,'h', 8], ['b' ,'c', 1], ['b' ,'f', 4], ['e' ,'f', 6], ['h' ,'i', 8], ['c' ,'f', 3], ['f' ,'i', 2], ['c' ,'d', 6], ['f' ,'g', 5], ['i' ,'g', 1], ['i' ,'j', 3], ['d' ,'g', 3], ['g' ,'j', 2], ['d' ,'z', 1], ['g' ,'z', 1], ['j' ,'z', 3]]
	adj = {}

	for c in all_c:
		adj[c]=[]

	for p in info:
		f,t,c = p
		adj[f].append([t,c])
		adj[t].append([f,c])

	return adj



def dij():
	adj = make_graph()
	L={}
	T = set()
	for c in all_c:
		L[c]=100000
		T.add(c)
	L['a']=0

	while('z' in list(T)):
		v,lv = choose_v(T,L)
		T.remove(v)
		print(str(v).upper()+' with cost '+str(lv))
		for there_index in range(len(adj[v])):
			x = adj[v][there_index][0]
			w_vx = adj[v][there_index][1]

			if x not in list(T):
				continue

			L[x]=min(L[x] , L[v] + w_vx)




dij()


# A with cost 0
# E with cost 1
# B with cost 4
# C with cost 5
# H with cost 6
# F with cost 7
# I with cost 9
# G with cost 10
# D with cost 11
# Z with cost 11
