import sys
from hashlib import sha256

from random import randrange
from random import randint

def extended_gcd(a: int, b: int) -> (int, int, int):
    if not a:
        return 0, 1, b
    
    x, y, gcd = extended_gcd(b % a, a)
    return y - (b // a) * x, x, gcd


def binary_power_modulo(num: int, power: int, modulo: int) -> int:
    if power < 0:
        raise ValueError('Power less than zero.')
        
    result: int = 1
    
    while power:
        if power % 2:
            result = (result * num) % modulo;
            
        num = (num * num) % modulo;
        power //= 2
	
    return result;


def generate_key(q: int) -> ((int, int, int), int, int):
    while True:
        r: int = randrange(0, 4 * (q + 1), 2)
        p: int = q * r + 1
        
        if binary_power_modulo(2, q * r, p) == 1 and binary_power_modulo(2, r, p) != 1:
            break
    
    while True:
        x: int = randint(0, p - 1)
        g: int = binary_power_modulo(x, r, p)
        
        if g != 1:
            break
    
    d: int = randint(0, q - 1)
    e: int = binary_power_modulo(g, d, p)
    
    return (p, q, g), e, d
    

def sign(p: int, q: int, g: int, d: int, message: str) -> (int, int):
    if d not in range(0, q):
        raise ValueError('D is not in [0, Q).')
    
    m: int = int(sha256(message.encode('utf-8')).hexdigest(), 16)
    k: int = randint(1, q - 1)
    
    r: int = binary_power_modulo(g, k, p)
    
    k_inverse: int = extended_gcd(k, q)[0]
    k_inverse = (k_inverse % q + q) % q
    
    s: int = (k_inverse * (m - d * r)) % q
    
    return r, s


def verify(p: int, q: int, g: int, e: int, message: str, r: int, s: int) -> bool:
    if e not in range(0, p):
        raise ValueError('E is not in [0, P).')
    
    if r not in range(1, p) or s not in range(0, q):
        return False
    
    m: int = int(sha256(message.encode('utf-8')).hexdigest(), 16)
    
    if (binary_power_modulo(e, r, p) * binary_power_modulo(r, s, p)) % p == binary_power_modulo(g, m, p):
        return True
    return False


def main() -> None:
    command: str = ''
    args: list = []
    
    while True:
        command, *args = input().split(' ')
        
        try:
            if command == 'Gen':
                params, e, d = generate_key(*[int(arg) for arg in args])
                
                print('---------------------------------------------------')
                print('P:', params[0])
                print('Q:', params[1])
                print('G:', params[2])
                print('E:', e)
                print('D:', d, '\n')
                
            elif command == 'Sign':
                print('Input message:')
                message = input()
                
                p, q, g, d = [int(arg) for arg in args]
                r, s = sign(p, q, g, d, message)
                
                print('---------------------------------------------------')
                print('R:', r)
                print('S:', s, '\n')
                
            elif command == 'Verify':
                print('Input message:')
                message = input()
                
                p, q, g, e, r, s = [int(arg) for arg in args]
                result = verify(p, q, g, e, message, r, s)
                
                print('---------------------------------------------------')
                print('Result:', result, '\n')
            
            elif command == 'Exit':
                
                print('---------------------------------------------------')
                print('Exiting . . .')
                return
            
            else:
                print('---------------------------------------------------')
                print('Unknown command, please try again.\n')
        except ValueError as error:
            print('---------------------------------------------------')
            print(error)

if __name__ == '__main__':
    main()
    sys.exit()
