import os
import random
import numpy as np
from numpy import savetxt
from numpy import genfromtxt


# path = "/content/drive/MyDrive/colab_notebooks/AI/AI_2"

# /content/drive/MyDrive/colab_notebooks/AI/AI_2/Desdemona

cmd1 = './bin/Desdemona ./bots/MyBot/bot.so ./bots/RandomBot/RandomBot.so'
  
cmd2 = './bin/Desdemona ./bots/RandomBot/RandomBot.so ./bots/MyBot/bot.so'

points_table = {}
hash_func = {}

# param_corp = [np.zeros([8,8])]*7
# for i in range(7):
#   cntr = 0
#   tp = np.fromstring(input().rstrip() , dtype=int, sep=' ')
#   while( len(tp) == 8 and cntr<8 ):
#       param_corp[cntr] = tp
#       cntr +=1
#       tp = np.fromstring(input().rstrip() , dtype=int, sep=' ')

#   param_corp[i][cntr][0] = 
#   param_corp[i][cntr][0] =
#   param_corp[i][cntr][0] =
#   param_corp[i][cntr][0] =


# File reading afterwards

#  [a, b, c, d, e, f, g, h]

# a b d e 
# b c f f
# d f g h
# e f h h


# init_lst = [A1,A2,A3,A4,A5,A6,A7,A8,A9,A10,A11,A12,A13,A14,A15,A16,A17,A18,A19,A20]

pop_size = 40

# par_cnt = len(init_lst)

# P_C = np.zeros([pop_size,8])

# for i in range(pop_size):
# 	if i< par_cnt:
# 		P_C[i] = np.array(init_lst[i])

# 	if i>= par_cnt:
# 		x = random.random()
# 		p1=0
# 		p2=0
# 		while(p1==p2):
# 			p1 = random.randint(0, par_cnt - 1)
# 			p2 = random.randint(0, par_cnt - 1)
# 		P_C[i] = x*(P_C[p1]) + (1-x)*(P_C[p2])

P_C = genfromtxt('/content/drive/MyDrive/colab_notebooks/AI/AI_2/Desdemona/data.csv', delimiter=',')
#  P_C ---> size 20, contains all 1x8 numpy arrays

# P_C[2][0]

def cross_over(i,j,w1,w2):
	x = w1/(w1+w2)
	res = i*x + (1-x)*j
	return res



def reset_table():
	for i in range(pop_size):
		points_table[i] = 0


def write2(a,b,c,d,e,f,g,h):
	file1 = open("/content/drive/MyDrive/colab_notebooks/AI/AI_2/Desdemona/file2.txt","w")

	file1.write(str(a)+" "+str(b)+" "+str(d)+" "+str(e)+" "+str(e)+" "+str(d)+" "+str(b)+" "+str(a)+"\n")
	file1.write(str(b)+" "+str(c)+" "+str(f)+" "+str(f)+" "+str(f)+" "+str(f)+" "+str(c)+" "+str(b)+"\n")
	file1.write(str(d)+" "+str(f)+" "+str(g)+" "+str(h)+" "+str(h)+" "+str(g)+" "+str(f)+" "+str(d)+"\n")
	file1.write(str(e)+" "+str(f)+" "+str(h)+" "+str(h)+" "+str(h)+" "+str(h)+" "+str(f)+" "+str(e)+"\n")
	file1.write(str(e)+" "+str(f)+" "+str(h)+" "+str(h)+" "+str(h)+" "+str(h)+" "+str(f)+" "+str(e)+"\n")
	file1.write(str(d)+" "+str(f)+" "+str(g)+" "+str(h)+" "+str(h)+" "+str(g)+" "+str(f)+" "+str(d)+"\n")
	file1.write(str(b)+" "+str(c)+" "+str(f)+" "+str(f)+" "+str(f)+" "+str(f)+" "+str(c)+" "+str(b)+"\n")
	file1.write(str(a)+" "+str(b)+" "+str(d)+" "+str(e)+" "+str(e)+" "+str(d)+" "+str(b)+" "+str(a)+"\n")

	file1.close()

def write1(a,b,c,d,e,f,g,h):
	
	file1 = open("/content/drive/MyDrive/colab_notebooks/AI/AI_2/Desdemona/file1.txt","w")

	# with open('readme.txt', 'w') as f:
	#     f.write('Create a new text file!')


	file1.write(str(a)+" "+str(b)+" "+str(d)+" "+str(e)+" "+str(e)+" "+str(d)+" "+str(b)+" "+str(a)+"\n")
	file1.write(str(b)+" "+str(c)+" "+str(f)+" "+str(f)+" "+str(f)+" "+str(f)+" "+str(c)+" "+str(b)+"\n")
	file1.write(str(d)+" "+str(f)+" "+str(g)+" "+str(h)+" "+str(h)+" "+str(g)+" "+str(f)+" "+str(d)+"\n")
	file1.write(str(e)+" "+str(f)+" "+str(h)+" "+str(h)+" "+str(h)+" "+str(h)+" "+str(f)+" "+str(e)+"\n")
	file1.write(str(e)+" "+str(f)+" "+str(h)+" "+str(h)+" "+str(h)+" "+str(h)+" "+str(f)+" "+str(e)+"\n")
	file1.write(str(d)+" "+str(f)+" "+str(g)+" "+str(h)+" "+str(h)+" "+str(g)+" "+str(f)+" "+str(d)+"\n")
	file1.write(str(b)+" "+str(c)+" "+str(f)+" "+str(f)+" "+str(f)+" "+str(f)+" "+str(c)+" "+str(b)+"\n")
	file1.write(str(a)+" "+str(b)+" "+str(d)+" "+str(e)+" "+str(e)+" "+str(d)+" "+str(b)+" "+str(a)+"\n")

	file1.close()

def func():
	os.system(cmd1)
	os.system(cmd2)
	with open("scores.txt", "r") as txt_file:
		lst = txt_file.readlines()
		lst[0].replace('\n','')
		lst[1].replace('\n','')
		firstgame = lst[0].split()
		secondgame = lst[1].split()
		a = int(firstgame[0])
		b = int(firstgame[1])
		c = int(secondgame[0])
		d = int(secondgame[1])
		score1=0
		score2=0
		if a > b:
			score1 += (64 + a)
			score2 += b
		elif a < b:
			score1 += a
			score2 += (64+b)
		else:
			score1 += a
			score2 += b

		if c > d:
			score1 += (64 + c)
			score2 += d
		elif c < d:
			score1 += c
			score2 += (64+d)
		else:
			score1 += c
			score2 += d
		
	os.remove('scores.txt')

	return (score1,score2)


#create 14 matrices using crossover.

def Genetic(pop_cands, pop_size, points_table, crossover_prob):   # (P_C, ##, ##)
	no_params = len(P_C[0])
	# crossover_prob = 0.5            ### No. of childs replacing the parents in each generation
	mutation_prob = 0.01

	# pop_cands = np.zeros([pop_size,no_params], dtype=int)
	fitness = np.zeros(pop_size)
	k = int((1-crossover_prob)*pop_size)

	for i in range(pop_size):
		fitness[i] = points_table[i]
	
	sel_probs = fitness / np.sum(fitness)
	matin_pool_indx = np.random.choice( pop_size , pop_size, p=sel_probs)

	part_1 = pop_cands[matin_pool_indx[:len(matin_pool_indx)//2]]
	ind1 = []
	ind2 = []
	part_2 = pop_cands[matin_pool_indx[len(matin_pool_indx)//2:]]
	

	for i in range(len(part_1)):
		for j in range(pop_size):
			if np.all(part_1[i] == pop_cands[j]):
				ind1.append(j)
	for i in range(len(part_2)):
		for j in range(pop_size):
			if np.all(part_2[i] == pop_cands[j]):
				ind2.append(j)


	child_pool = np.zeros([20,8])

	birth = 0
	# fitness_child = np.zeros(pop_size)

	while(birth < pop_size/2):
		m_1 = random.randint(0,(len(matin_pool_indx)//2)-1)
		m_2 = random.randint(0,(len(matin_pool_indx)//2)-1)

		child_pool[birth] = cross_over(part_1[m_1], part_2[m_2],fitness[ind1[m_1]],fitness[ind2[m_2]])
		# fitness_child[birth], fitness_child[birth+1] = path_cost_adj(child_pool[birth]), path_cost_adj(child_pool[birth+1])
		# fitness_child[birth], fitness_child[birth+1] = func(mat1,mat2)
		
		birth = birth + 1
	
	# child_pool = mutate(child_pool, mutation_prob, no_params)           ##### MUTATION ON PENDING!!! and have to calculate fitness after mutating!

	# for i in range(pop_size):s
	#   fitness_child[i] = path_cost_adj(child_pool[i])
	# # fitness_child = 1/fitness_child
	# pop_cands[fitness.argsort()[:k]] = child_pool[fitness_child.argsort()[:k]]      ### [::-1] incase if using inverse fitness
	# for i in range(pop_size):
	#   fitness[i] = path_cost_adj(pop_cands[i])
	
	# best_path = pop_cands[fitness.argsort()[0]]

	return child_pool

	#points table is updated,sort the table somehow and remove last 10
	#randomly crossover best 10, mutate with less chance

#take all possible pairs and call func() and update points table.points

def bubbleSort(arr, P_C):
	n = len(arr)
 
	# Traverse through all array elements
	for i in range(n-1):
	# range(n) also work but outer loop will repeat one time more than needed.
 
		# Last i elements are already in place
		for j in range(0, n-i-1):
 
			# traverse the array from 0 to n-i-1
			# Swap if the element found is greater
			# than the next element
			if arr[j] < arr[j + 1] :
				arr[j], arr[j + 1] = arr[j + 1], arr[j]
				P_C[j], P_C[j + 1] = P_C[j + 1], P_C[j]

gen = 3


itr=0

for gen_iter in range(gen):
	#round robin for the generation, ETA ~ 30 min
	reset_table()
	itr = 0

	for i in range(pop_size):
		for j in range(pop_size):
			itr = itr + 1
			print("Gen " + str(gen_iter) + ": Pair number: " + str(itr))
			if j <= i:
				continue
			mat1 = P_C[i]
			mat2 = P_C[j]

			write1(mat1[0],mat1[1],mat1[2],mat1[3],mat1[4],mat1[5],mat1[6],mat1[7])
			write2(mat2[0],mat2[1],mat2[2],mat2[3],mat2[4],mat2[5],mat2[6],mat2[7])

			val = func()

			points_table[i] += val[0]
			points_table[j] += val[1]
			os.remove('file1.txt')
			os.remove('file2.txt')

	savetxt('data'+str(gen_iter)+'.csv', P_C, delimiter=',')
	if gen_iter == (gen - 1):
	 break
	# genetic here - use points_table
	crossover_prob = 0.5
	c_pool = Genetic(P_C,pop_size, points_table, crossover_prob)

	points_list = []
	sortlist = []
	for i in range(pop_size):
		sortlist.append(P_C[i].tolist())
	for i in range(pop_size):
		points_list.append(points_table[i])

	bubbleSort(points_list,sortlist)

	for i in range(pop_size):
		P_C[i] = np.array(sortlist[i])

	P_C[int(pop_size*crossover_prob):] = c_pool


savetxt('data.csv', P_C, delimiter=',')

