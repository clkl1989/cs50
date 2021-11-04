from cs50 import get_int
# ask user for credit card number
def main():
    N = get_int("Number:")
    
    if check_length(N) == True:
        if check_sum(N) == True:
            check_card(N)
        
        else:
            print("INVALID")
         
    else:
        print("INVALID")


def check_length(N):
    if len(str(N)) == 13 or len(str(N)) == 15 or len(str(N)) == 16:
        return True
    else:
        return False
        
def check_sum(N):
    
    #1: identify digits to multiply by 2 (second last onwards)
    #2: get product of 2xdigit
    #3: add all prod as sumprod
    #4: add all nonmultiplydigit and sumprod to get checksum
    #5: checksum divide by 10, if remainder == 0, valid CC number
    
    checksum = 0
    
    for p in range(len(str(N))):
        
        if p % 2 == 0: 
            digit = int(str((N % (10 ** (p+1))) - (N % (10 ** p)))[:1])
        else: 
            temp = (N % (10 ** (p+1))) - (N % (10 ** p))
            temp = 2 * int(temp)
            if len(str(temp)) > 1:
                digit = sum([int(x) for x in str(temp)])
            else:
                digit = temp
            
        checksum += digit
            
        #print(f"{p} + {digit} + {checksum}") #to be removed
            
    if checksum % 10 == 0:
        return True
    
    else:
        return False


def check_card(N):
    
    #check if number starts with 34 or 37 -> American Express
    if int(str(N)[:2]) == 34 or int(str(N)[:2]) == 37:
        print("AMEX")
        
    
    #check if number starts with 4 -> VISA    
    elif int(str(N)[:1]) == 4:
        print("VISA")
    
    #check if number starts with 51, 52, 53, 54, 55 -> Mastercard
    elif int(str(N)[:2]) in range(51,56):
        print("MASTERCARD")
    
    #otherwise -> invalid number    
    else:
        print("INVALID")
        
        
    
main()
    
   


