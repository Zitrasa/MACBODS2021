import sys

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
    

def output_line(stream = sys.stdout):
    print('----------------------------------------------------------------\n',
          file=stream)

def generate_key(p: int, q: int, e: int) -> (int, int):
    modulo: int = p * q
    phi: int = (p - 1) * (q - 1)
    
    x, y, gcd = extended_gcd(e, phi)
    if gcd != 1:
        raise ValueError('Invalid P, Q, E: GCD(Key, EulerPhi) is not 1.')
    
    private_key = (x % phi + phi) % phi
    return private_key, modulo


def encrypt(message: int, open_key: int, modulo: int) -> int:
    if message >= modulo:
        raise ValueError('Encryption message not in Z.')
    
    return binary_power_modulo(message, open_key, modulo)


def decrypt(message: int, private_key: int, modulo: int) -> int:
    if message >= modulo:
        raise ValueError('Decryption message not in Z.')
    
    return binary_power_modulo(message, private_key, modulo)
    

def main() -> None:
    command: str = ''
    args: list = []
    
    while True:
        command, *args = input().split(' ')
        
        try:
            if command == 'Gen':
                private_key, modulo = generate_key(*[int(arg) for arg in args])
                output_line()
                print('Private key:', private_key)
                print('Modulo:', modulo)
                output_line()
            elif command == 'Encr':
                encrypted = encrypt(*[int(arg) for arg in args])
                output_line()
                print('Encrypted:', encrypted)
                output_line()
            elif command == 'Decr':
                decrypted = decrypt(*[int(arg) for arg in args])
                output_line()
                print('Decrypted:', decrypted)
                output_line()
            elif command == 'Exit':
                output_line()
                print('Exiting...')
                return
            else:
                print('Unknown command, please try again.')
        except ValueError as error:
            print(error)

if __name__ == '__main__':
    main()
    exit()