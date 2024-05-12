class ReadEliminateSignFromPaper:
    def __init__(self, file):
        # chnaging the way of file I/O is possible
        with open(file, 'r', encoding='utf8') as f:
            paper = f.readlines() # a list that contains paragraph-wise elements. note: each paragraph has different number of sentences
            
        self.sign_dict = dict() # a dictionary whose key and value are the eliminated sign and the number of that sign, respectively
        self.sentences = list() # a list that contains sentence-wise elements
        self.cnt = 0
        # changing data-type or name of variables above is possible
        
        #########################################################
        # complete the code below, following assignment guideline
        
        
        tem=list()
        for i in range(len(paper)):
            for j in range(len(paper[i].split())):       
                tem.append(paper[i].split()[j])
        lis=''
        for i in range(len(tem)):
            lis += self.find_eliminate_sign(tem[i])
            if(self.cnt==0):
                lis += ' '
            else:
                lis.rstrip()
                self.sentences.append(lis)
                self.cnt=0
                lis=''
        

        #########################################################
    
    """it is impossible to change the name of methods (functions) below"""
    def find_eliminate_sign(self, word):
        '''find all signs and eliminate them from given "word"
           (except the period(.) that makes the End Of Sentence)
           and return it
        '''
        
        no_sign_word = '' # changing this variable also okay
        #########################################################
        # complete the code below, following assignment guideline
        if(word.isalnum()):
            no_sign_word=word
        else:
            if(word[len(word)-1]=='.'):
                for i in range(len(word)-1):
                    if(word[i].isalnum()):
                        no_sign_word += word[i]
                    else:
                        if(word[i] in self.sign_dict):
                            self.sign_dict[word[i]] += 1
                        else:
                            self.sign_dict[word[i]] = 1
                no_sign_word += '.'

                self.cnt = 1
                no_sign_word=word
            else:
                for i in range(len(word)):
                    if(word[i].isalnum()):
                        no_sign_word += word[i]
                    else:
                        if(word[i] in self.sign_dict):
                            self.sign_dict[word[i]] += 1
                        else:
                            self.sign_dict[word[i]] = 1



        #########################################################
        return no_sign_word
    
    def get_sorted_sign(self):
        '''return a list 
           that contains (eliminated sign, the number of that sign) tuples 
           and is sorted by the number in descending
        '''
        #########################################################
        # complete the code below, following assignment guideline

        return sorted(self.sign_dict.items(), key=lambda x:x[1], reverse=True)
        #########################################################
    
    def __len__(self):
        '''return the number of sentences'''
        #########################################################
        # complete the code below, following assignment guideline
        return len(self.sentences)
        #########################################################
        
    def __getitem__(self, idx):
        """return a sentence that corresponds to the given index "idx" """
        #########################################################
        # complete the code below, following assignment guideline
        return self.sentences[idx]
        #########################################################

