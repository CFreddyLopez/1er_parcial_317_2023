
import multiprocessing

def es_Palindrome(word):
    return word == word[::-1]

def find_Palindromes(words):
    pool = multiprocessing.Pool()
    results = pool.map(es_Palindrome, words)    
    pool.close()
    pool.join()
    return results

if __name__ == '__main__':
    words = []
    word = input('Ingrese una palabra o escriba "exit" para salir: ')
    words.append(word)
    results = find_Palindromes(words)
    for i, word in enumerate (words):
        print(word, 'es un palindrome' if results[i] else 'no es un palindrome')
            
    
    
