import os;


DICTIONARY = b'abcdefghijklmnopqrstuvwxyz'
key_sizes = [ 1, 10, 100, 1000, 10000, 100000 ]
file_sizes = [ 1, 10, 100, 1000, 10000, 100000 ]
command = "./bvernam"

experiments = [ (lambda : DICTIONARY,1,len(DICTIONARY)),\
                (lambda : DICTIONARY,1,10*len(DICTIONARY)),\
                (lambda : DICTIONARY,1,100*len(DICTIONARY)),\
                (lambda : DICTIONARY,1,1000*len(DICTIONARY)),\
                (lambda : DICTIONARY,1,10000*len(DICTIONARY)),\
                (lambda : DICTIONARY,1,100000*len(DICTIONARY)),\
                (lambda : DICTIONARY,1,100),\
                (lambda : DICTIONARY,1,1000),\
                (lambda : DICTIONARY,1,10000),\
                (lambda : bytes(range(1,256)),1,256),\
                (lambda : bytes(range(1,256)),1,10000),\
                (lambda : bytes(range(1,256))*10,1,10000),\
                (lambda : bytes(range(1,256))*100,1,100000),\
                (lambda : bytes(range(1,256))*1000,1,1000000),\
                (lambda : bytes(range(1,20))*10000000,1,1000000) ]
                
                

def run_encoding(keyfile, datafile, outputfile):
    os.system(command+" "+keyfile+" "+datafile+" "+outputfile)
    

def write_data_to_file(data, n, filename):
    with open(filename,'wb') as f:        
        for i in range(n):
            f.write(data)


            
def check_equals(filename, expected, actual, frm, to):
    for i in range(frm,to):
        if expected[i-frm] != actual[i]:
            print("ERROR: file "+filename+" byte "+str(i)+" "+str(expected[i-frm])+" "+str(actual[i]))
            return False
    return True



def shift(data):
    return [ data[(i+1)%len(data)] for i in range(len(data)) ]

            
            
def check_file_content(data, n, filename):
    counter = 0
    data_length = len(data)
    try:
        f = open(filename,'rb')
        content = f.read()
    except:
        print("ERROR: "+filename+" non esiste!!!")
        return 0
    if n != len(content):
        print("ERROR: Errore nel contentenuto di "+filename)
        print("Attesi "+str(n))
        print("Generati "+str(len(content)))
        return 0
    while counter<len(content):
        if not check_equals(filename,data,content,counter,min(counter+len(data),len(content))):
             return 0
        counter = counter+len(data)
        data = shift(data)
    return 1


def test_result(data, copies, zeroes, fileprefix):
    keyfile =fileprefix + "_key"
    datafile = fileprefix + "_data"
    outputfile = fileprefix + "_out"
    write_data_to_file(data,copies, keyfile)
    write_data_to_file(bytes(zeroes),1,datafile)
    run_encoding(keyfile, datafile, outputfile)
    return check_file_content(data*copies,zeroes,outputfile)


def get_encoded_file(key,n,file):
    with open(file,'wb') as f:
        counter = 0
        while counter < n:
            if (counter+len(key)>n):
                f.write(bytes(key[:n-counter]))
                counter = n
            else:
                f.write(bytes(key))
                key = shift(key)
                counter = counter+len(key)





if __name__ == "__main__":
    counter = 0
    mark = 0
    for (datafun, copies, zeroes) in experiments:
        counter = counter+1;
        print("Test"+str(counter)+"\n")
        mark += test_result(datafun(),copies,zeroes,"test"+str(counter))
    print("Totale "+str(mark)+"/"+str(counter))
