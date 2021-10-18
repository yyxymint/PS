def hex_to_list(hx):
    f_map={}
    to=0
    for i in '0123456789ABCDEF':
        f_map[i]=to
        to+=1
    
    ll=[
        [0,0,0,0],
        [0,0,0,1],
        [0,0,1,0],
        [0,0,1,1],
        [0,1,0,0],
        [0,1,0,1],
        [0,1,1,0],
        [0,1,1,1],
        [1,0,0,0],
        [1,0,0,1],
        [1,0,1,0],
        [1,0,1,1],
        [1,1,0,0],
        [1,1,0,1],
        [1,1,1,0],
        [1,1,1,1],
    ]
    return ll[f_map[hx[0]]]+ll[f_map[hx[1]]]


def reverse_list(l):
    return l[::-1]


def list_to_poly(li):
    # 왼쪽이 1, 오른쪽이 x^n
    ret=''
    seed = len(li)-1
    for i in range(len(li)-1,-1,-1):
        if li[i]==1:
            if i>0:
                ret+='x^'+str(seed)+' + '
            else:
                ret+='1'+' + '
        seed-=1
    return ret[:-3]

def poly_calculator(f,g,p=[1,0,0,0,1,1,0,1,1],view=True):
    ret=[]
    mlen=0
    for i in range(len(g)-1,-1,-1):
        if g[i]==1:
            inn=[0 for _ in range(len(g)-i-1)]
            inn+=reverse_list(f)
            ret.append(inn)
            mlen=max(mlen,len(inn))
    
    for i in range(len(ret)):
        while len(ret[i])<mlen:
            ret[i].append(0)

    modulo = []
        
    for j in range(mlen):
        s=0
        for i in range(len(ret)):
            s+=ret[i][j]
        s%=2
        modulo.append(s)
    
    if view:
        print('f(x) = '+list_to_poly(reverse_list(f)))
        print('g(x) = '+list_to_poly(reverse_list(g)))
        print('p(x) = '+list_to_poly(reverse_list(p)))
        print()

        print('f(x)*g(x) = '+list_to_poly(modulo))
        print()

    
    modulo = reverse_list(modulo)
    
    for check_pos in range(len(modulo)-len(p)+1):
        if modulo[check_pos]==1 and p[0]==1:
            for xor_pos in range(len(p)):
                modulo[check_pos + xor_pos] = modulo[check_pos + xor_pos]^p[xor_pos]
            if view:
                print('modulo is equivalent to '+list_to_poly(reverse_list(modulo)))
        
    return modulo[-8:]
    

def inverse_finder(A_i, divider=[1,0,0,0,1,1,0,1,1],view=True):
    if view:
        print('input Hex : '+list_to_poly(reverse_list(A_i)))
    for a1 in [0,1]:
        for a2 in [0,1]:
            for a3 in [0,1]:
                for a4 in [0,1]:
                    for a5 in [0,1]:
                        for a6 in [0,1]:
                            for a7 in [0,1]:
                                for a8 in [0,1]:
                                    trial = [a1,a2,a3,a4,a5,a6,a7,a8]
                                    if poly_calculator(trial,A_i,divider,view=False)==[0,0,0,0,0,0,0,1]:
                                        if view:
                                            print(list_to_poly(reverse_list(trial)))
                                        return trial
                                        
def gf_matrix(B_i_prime):
    
#     print(" b'0 ~ b'7 : "+str(B_i_prime))
    b_list=[]
    just_sum=[]
    mat=[
        [1,0,0,0,1,1,1,1],
        [1,1,0,0,0,1,1,1],
        [1,1,1,0,0,0,1,1],
        [1,1,1,1,0,0,0,1],
        [1,1,1,1,1,0,0,0],
        [0,1,1,1,1,1,0,0],
        [0,0,1,1,1,1,1,0],
        [0,0,0,1,1,1,1,1]
    ]
    
    bias_list=[1,1,0,0,0,1,1,0]
    
    for i in range(8):
        s=bias_list[i]
        for j in range(8):
            s+=mat[i][j]*B_i_prime[j]
        b_list.append(s%2)
        just_sum.append(s-bias_list[i])
    
#     print(" b0 ~ b7 : "+str(b_list))



###################################################
    start_char = '┌││││││└'
    end_char = '┐││││││┘'
    equal_line='   =    '
    add_line='   +    '
    

    for line in range(8):
        
        #########
        print(start_char[line],end="")
        print('b'+str(line)+end_char[line],end=" ")
        #########
        
        print(equal_line[line],end=" ")
        
        #########
        print(start_char[line],end="")
        print(b_list[line],end="")
        print(end_char[line],end=" ")
        #########
        
        
        print(equal_line[line],end="")
        
        
        #########
        print(' '+start_char[line],end="")
        for j in range(8):
            print(mat[line][j],end=" ")
        print(end_char[line],end="")
        #########
        #########
        print(start_char[line],end="")
        print("b'"+str(line)+end_char[line],end="")
        #########
        #########
        print(add_line[line],end="")
        print(start_char[line]+str(bias_list[line]),end="")
        print(end_char[line],end=" ")
        #########
        
        
        
        
        print(equal_line[line],end="")
        
        
        #########
        print(' '+start_char[line],end="")
        for j in range(8):
            print(mat[line][j],end=" ")
        print(end_char[line],end="")
        #########
        #########
        print(start_char[line],end="")
        print(str(B_i_prime[line])+end_char[line],end="")
        #########
        #########
        print(add_line[line],end="")
        print(start_char[line]+str(bias_list[line]),end="")
        print(end_char[line],end=" ")
        #########
        print(equal_line[line],end=" ")
        
        
        
        #########
        print(start_char[line]+str(just_sum[line]),end="")
        print(end_char[line],end="")
        print(add_line[line],end="")
        print(start_char[line]+str(bias_list[line]),end="")
        print(end_char[line],end=" ")
        #########
        print(equal_line[line],end=" ")
        print(start_char[line]+str(b_list[line]),end="")
        print(end_char[line],end="")
        print()
    
    print()
    print('b7 ~ b0 is : '+str(reverse_list(b_list)))
    return b_list

def list_to_hex_number(li):
    ret=0
    seed=8
    for i in range(4):
        ret+=li[i]*seed
        seed//=2
    return ret
    
    
    
def sbox(input_hex,divider=[1,0,0,0,1,1,0,1,1]):
    hex_to_alpha = '0123456789ABCDEF'
    print('input num is : '+hex_to_alpha[list_to_hex_number(input_hex[:4])]+hex_to_alpha[list_to_hex_number(input_hex[4:8])])
    print('It is equivalent to '+list_to_poly(reverse_list(input_hex)))
    print()
    
    B_i_prime = inverse_finder(input_hex, view=False)
    
    print("Inverse (B'_i) is : "+list_to_poly(reverse_list(B_i_prime)))
    print()
    print()
    B_i = gf_matrix(reverse_list(B_i_prime))
    print('It is equivalent to '+list_to_poly(B_i))
    print('In HEX, : '+hex_to_alpha[list_to_hex_number(reverse_list(B_i)[:4])]+hex_to_alpha[list_to_hex_number(reverse_list(B_i)[4:])])
    
    
    
def multiply_four_element(arr1,arr2,view=True):
    ret=[0 for _ in range(8)]
    for c in range(4):
        ele1 = hex_to_list(arr1[c])
        ele2 = hex_to_list(arr2[c])
        
        temp = poly_calculator(ele1,ele2,view=False)
        for t in range(8):
            ret[t]+=temp[t]
            ret[t]%=2
    if view:
        print(list_to_poly(reverse_list(ret)))
    return ret
    
    
    
def mix_columns(input_list):
    hex_to_alpha = '0123456789ABCDEF'
    
    large_list=[[],[],[],[]]
 
    large_list[0].append('02')
    large_list[0].append('03')
    large_list[0].append('01')
    large_list[0].append('01')
    
    large_list[1].append('01')
    large_list[1].append('02')
    large_list[1].append('03')
    large_list[1].append('01')
    
    large_list[2].append('01')
    large_list[2].append('01')
    large_list[2].append('02')
    large_list[2].append('03')
    
    large_list[3].append('03')
    large_list[3].append('01')
    large_list[3].append('01')
    large_list[3].append('02')
    
    
    ret_list=[[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]]
    
    save_list=[[],[],[],[]]
    
    for i in range(4):
        for j in range(4):
            select_col_j = [input_list[0][j],input_list[1][j],input_list[2][j],input_list[3][j]]
            
            temp = multiply_four_element(large_list[i],select_col_j,view=False)
            ret_list[i][j]=temp
            print(hex_to_alpha[list_to_hex_number(temp[:4])]+hex_to_alpha[list_to_hex_number(temp[4:])],end=" ")
        print()
            
def inv_mix_columns(input_list):
    hex_to_alpha = '0123456789ABCDEF'
    
    large_list=[[],[],[],[]]
 
    large_list[0].append('0E')
    large_list[0].append('0B')
    large_list[0].append('0D')
    large_list[0].append('09')
    
    large_list[1].append('09')
    large_list[1].append('0E')
    large_list[1].append('0B')
    large_list[1].append('0D')
    
    large_list[2].append('0D')
    large_list[2].append('09')
    large_list[2].append('0E')
    large_list[2].append('0B')
    
    large_list[3].append('0B')
    large_list[3].append('0D')
    large_list[3].append('09')
    large_list[3].append('0E')
    
    
    ret_list=[[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]]
    
    save_list=[[],[],[],[]]
    
    for i in range(4):
        for j in range(4):
            select_col_j = [input_list[0][j],input_list[1][j],input_list[2][j],input_list[3][j]]
            
            temp = multiply_four_element(large_list[i],select_col_j,view=False)
            ret_list[i][j]=temp
            print(hex_to_alpha[list_to_hex_number(temp[:4])]+hex_to_alpha[list_to_hex_number(temp[4:])],end=" ")
        print()
        
        
        
import math
def finding_p_q(n,pi_n):
    p_plus_q=1+n-pi_n
    print('p+q = '+str(p_plus_q))
    
    print('solve x^2 -'+str(p_plus_q)+'x +'+str(n)+' = 0')
    print('b^2 = '+str(p_plus_q**2))
    print('4ac = '+str(4*n))
    print('b^2-4ac = '+str(p_plus_q**2-4*n))
    print('sqrt(b^2-4ac) = '+str(math.sqrt(p_plus_q**2-4*n)))
    
    print()
    print('x are :')
    print((p_plus_q+int(math.sqrt(p_plus_q**2-4*n)))//2)
    print((p_plus_q+int(math.sqrt(p_plus_q**2+4*n)))//2)
    
