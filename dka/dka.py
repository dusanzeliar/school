#!/usr/bin/python

#DKA:xzelia00



 # syn.php
 # Implementacia Determinizacie konecneho automatu, 12.4.2014
 # Autor: Dusan Zeliar,xzelia00, FIT.

import getopt, sys , pprint

insensitive=False


def help():
    print ("Skript spracuje a determinizuje konecny automat")
    print ("argumenty: no-epsilon-rules determinization case-insensitive output= input= help")
    print ("Autor: Dusan Zeliar xzelia00")
    sys.exit(0)

def argumentError():
    print ("Please use the correct arguments, for usage type --help")
    sys.exit(1)

def removeCommentsAndWhiteChars(input_file):
    c=input_file.read(1)
    state = "whitechar"
    while True:
        if not c:
            return
        if state == "whitechar":
            if c == '#':
                state = "comment"
            elif c == '\n' or c == '\r' or c == ' ' or c == '\t':
                state = "whitechar"
            else:
                break
        elif state == "comment":
            while True:
                #last=len(c.encode('utf-8'))
                c=input_file.read(1)
                if not c:
                    return
                if c == '\n' or c == '\r':
                    state = "whitechar"
                    break
        if c:
            c=input_file.read(1)
        else: return
    input_file.seek(input_file.tell()-len(c.encode('utf-8')))


def getState(input_file,states):
    global insensitive

    removeCommentsAndWhiteChars(input_file)
    c=input_file.read(1)
    identifier = ""
    #lowercase
    if insensitive:
        c=c.lower()
    identifier = identifier + c
    if not( ord(c) >= ord('a') and ord(c) <= ord('z') or ord(c) >= ord('A') and ord(c) <= ord('Z') ):
        return False 

    while True:
        c=input_file.read(1)
        #lowercase
        if insensitive:
            c=c.lower()
        if ord(c) >= ord('a') and ord(c) <= ord('z') or ord(c) >= ord('A') and ord(c) <= ord('Z') or c == '_' or ord(c) >= ord('0') and ord(c) <= ord('9') :
            identifier = identifier + c
            continue
        else:
            break
    #check if last char of identifier if not _
    if identifier.endswith('_'): 
        return False

    states.append(identifier)
    input_file.seek(input_file.tell()-1)

def getAplhabet(input_file,alphabets):
    removeCommentsAndWhiteChars(input_file)
    c=input_file.read(1)
    #lowercase
    if insensitive:
        c=c.lower()
    identifier = ""
    identifier = identifier + c
    if c != '\'':
        return False
    c=input_file.read(1)
    #lowercase
    if insensitive:
        c=c.lower()
    identifier = identifier + c
    if ord(c) < 127:
        if not ( ord(c) >= ord('a') and ord(c) <= ord('z') or ord(c) >= ord('A') and ord(c) <= ord('Z') or ord(c) >= ord('0') and ord(c) <= ord('9')
        or c == '(' or c == ')' or c == '{' or c == '}' or c == '-' or c == '>' or c == ',' or c == '.' or c == '#' or c == ' '):
            #check for '' or ''''
            if c == '\'':
                c=input_file.read(1)
                if c == '\'':
                    identifier = identifier + c
                    c=input_file.read(1)
                    identifier = identifier + c
                    if c != '\'':
                        return False
                else:
                    #push back char
                    input_file.seek(input_file.tell()-1)
            else:
                return False
        #one of chars obove, check ending '
        else:
            c=input_file.read(1)
            #lowercase
            if insensitive:
                c=c.lower()
            identifier = identifier + c
            if c != '\'':
                return False
    else:
        c=input_file.read(1)
        identifier = identifier + c
        if c != '\'':
            return False
    #add identifier to list
    alphabets.append(identifier)            
    return True

def programExit(input_file,output_file,ret_number):
    if input_file is not sys.stdin:
        input_file.close()
    if output_file is not sys.stdout:
        output_file.close()
    sys.exit(ret_number)

def getKey(item):
    return item[0]



def main():
    global insensitive
    try:
        opts, args = getopt.getopt(sys.argv[1:], "edi", ["no-epsilon-rules", "determinization","case-insensitive","output==","input==","help"])
    except getopt.GetoptError as err:
        # print help information and exit:
        print (" Please use the correct  arguments, for usage type --help ")
        argumentError()
    e_flag = False
    d_flag = False
    i_flag = False
    output_name = None
    input_name = None
    for option,value in opts:
        if option == "-e" or option == "--no-epsilon-rules":
            if e_flag == True or d_flag == True:
                argumentError()
            e_flag = True
        elif option == "-d" or option == "--determinization":
            if e_flag == True or d_flag == True:
                argumentError()
            d_flag = True
        elif option == "-i" or option == "--case-insensitive":
            if i_flag == True:
                argumentError()
            i_flag = True
        elif option == "--output=":
            if not (output_name is None):
                argumentError()
            output_name = value
        elif option == "--input=":
            if not (input_name is None):
                argumentError()
            input_name = value
        elif option == "--help":
            if not (len(opts) == 1):
                argumentError()
            help()
        else:
            argumentError()
    
    #pprint.pprint(locals())
    insensitive=i_flag


    #open files
    #default stdin
    input_file = sys.stdin
    if not (input_name is None):
        try:
            input_file =  open(input_name, "r")
        except IOError:
            print ("Failed to open input file")
            sys.exit(2)
    #output file or stdout
    #default stdout
    output_file = sys.stdout
    if not (output_name is None):
        try:
            output_file =  open(output_name, "w")
        except IOError:
            print ("Failed to open output file")
            #close input file
            programExit(input_file,output_file, 3)

    #create lists 
    states = []
    alphabets = []
    rules = []
    count_rules = 0
    start_state=[]
    final_states=[]


    state="start"
    c=1

    while True:
        #pprint.pprint(locals())
        #if not empty c, continue with parsing
        if not c:
            break
        #starting state 
        if state == "start":
            removeCommentsAndWhiteChars(input_file);
            c=input_file.read(1)
            if c != '(':
                programExit(input_file,output_file, 40)
            else:
                state = "start_set_of_states"

        #opening bracket of set of states
        elif state == "start_set_of_states":
            removeCommentsAndWhiteChars(input_file);
            c=input_file.read(1)
            if c != '{':
                programExit(input_file,output_file, 40)
            else:
                state = "state"

        #parsing states
        elif state == "state":
            #remove chars after
            removeCommentsAndWhiteChars(input_file);
            c=input_file.read(1)
            if c == '}' and len(states)==0:
                state = "comma_start_input_alphabet"
                continue
            else:
                input_file.seek(input_file.tell()-1)

            if getState(input_file,states) == False:
                programExit(input_file,output_file, 40)
            #remove chars after
            removeCommentsAndWhiteChars(input_file);
            c=input_file.read(1)
            if c == ',':
                continue
            elif c == '}':
                state = "comma_start_input_alphabet"
            else:
                programExit(input_file,output_file, 40)

        #comma before opening bracket of input alphabet
        elif state == "comma_start_input_alphabet":
            removeCommentsAndWhiteChars(input_file);
            c=input_file.read(1)
            if c != ',':
                programExit(input_file,output_file, 40)
            else:
                state = "start_input_alphabet"

        #opening bracket of input alphabet
        elif state == "start_input_alphabet":
            removeCommentsAndWhiteChars(input_file);
            c=input_file.read(1)
            if c != '{':
                programExit(input_file,output_file, 40)
            else:
                state = "alphabet"

        #parsing alphabet
        elif state == "alphabet":
            #remove chars after
            removeCommentsAndWhiteChars(input_file);
            c=input_file.read(1)
            if c == '}' and len(alphabets)==0:
                state = "comma_start_set_of_rules"
                continue
            else:
                input_file.seek(input_file.tell()-1)

            if getAplhabet(input_file,alphabets) == False:
                programExit(input_file,output_file, 40)
            #remove chars after
            removeCommentsAndWhiteChars(input_file);
            c=input_file.read(1)
            if c == ',':
                continue
            elif c == '}':
                state = "comma_start_set_of_rules"
            else:
                programExit(input_file,output_file, 40)

        #comma before opening bracket of set of rules
        elif state == "comma_start_set_of_rules":
            removeCommentsAndWhiteChars(input_file);
            c=input_file.read(1)
            if c != ',':
                programExit(input_file,output_file, 40)
            else:
                state = "start_set_of_rules"

        #opening bracket of input of set of rules
        elif state == "start_set_of_rules":
            removeCommentsAndWhiteChars(input_file);
            c=input_file.read(1)
            if c != '{':
                programExit(input_file,output_file, 40)
            else:
                state = "rule"

        #parsing rules
        elif state == "rule":
            rules.append([])

            #remove chars after
            removeCommentsAndWhiteChars(input_file);
            c=input_file.read(1)
            if c == '}' and len(rules)==1:
                state = "comma_start_state"
                rules.pop()
                continue
            else:
                input_file.seek(input_file.tell()-1)
            #start state
            if getState(input_file,rules[count_rules]) == False:
                programExit(input_file,output_file, 40)
            #alphabet
            if getAplhabet(input_file,rules[count_rules]) == False:
                programExit(input_file,output_file, 40)
            #remove chars after
            removeCommentsAndWhiteChars(input_file);
            #->
            c=input_file.read(1)
            if c != '-':
                programExit(input_file,output_file, 40)
            c=input_file.read(1)
            if c != '>':
                programExit(input_file,output_file, 40)
            #target state
            if getState(input_file,rules[count_rules]) == False:
                programExit(input_file,output_file, 40)
            count_rules = count_rules + 1

            #remove chars after
            removeCommentsAndWhiteChars(input_file);
            c=input_file.read(1)
            if c == ',':
                continue
            elif c == '}':
                state = "comma_start_state"
            else:
                programExit(input_file,output_file, 40)

        #comma before starting state
        elif state == "comma_start_state":
            removeCommentsAndWhiteChars(input_file);
            c=input_file.read(1)
            if c != ',':
                programExit(input_file,output_file, 40)
            else:
                state = "start_start_state"

        #start state
        elif state == "start_start_state":
            #remove chars after
            removeCommentsAndWhiteChars(input_file);
            c=input_file.read(1)
            if c == ',' and len(start_state)==0:
                state = "start_set_of_final_states"
                continue
            else:
                input_file.seek(input_file.tell()-1)
            if getState(input_file,start_state) == False:
                programExit(input_file,output_file, 40)
            #remove chars after
            removeCommentsAndWhiteChars(input_file);
            c=input_file.read(1)
            if c == ',':
                state = "start_set_of_final_states"
            else:
                programExit(input_file,output_file, 40)

        #opening bracket of set of final states
        elif state == "start_set_of_final_states":
            removeCommentsAndWhiteChars(input_file);
            c=input_file.read(1)
            if c != '{':
                programExit(input_file,output_file, 40)
            else:
                state = "final_states"

        #parsing final states
        elif state == "final_states":
            #remove chars after
            removeCommentsAndWhiteChars(input_file);
            c=input_file.read(1)
            if c == '}' and len(final_states)==0:
                state = "final_states_bracket"
                continue
            else:
                input_file.seek(input_file.tell()-1)

            if getState(input_file,final_states) == False:
                programExit(input_file,output_file, 40)
            #remove chars after
            removeCommentsAndWhiteChars(input_file);
            c=input_file.read(1)
            if c == ',':
                continue
            elif c == '}':
                state = "final_states_bracket"
            else:
                programExit(input_file,output_file, 40)

        #parsing final states
        elif state == "final_states_bracket":
            #endig bracket
            removeCommentsAndWhiteChars(input_file);
            c=input_file.read(1)
            if c != ')':
                programExit(input_file,output_file, 40)
            #remove white spaces and comments at the end
            removeCommentsAndWhiteChars(input_file);
            c=input_file.read(1)
            if c:
                programExit(input_file,output_file, 40)
        else:
            programExit(input_file,output_file, 40)

    #check if finite machine ended with eof
    #print "cau"
    if c or state != "final_states_bracket":
        programExit(input_file,output_file, 40)

    #pprint.pprint(locals())

    #remove duplicates
        #add identifier to list
    if states:
        for index1, val1 in enumerate(states):
            for index2, val2 in enumerate(states):
                if index2 <= index1:
                    continue
                elif val1 == val2:
                    states.pop(index2)
    if states:
        for index1, val1 in enumerate(states):
            for index2, val2 in enumerate(states):
                if index2 <= index1:
                    continue
                elif val1 == val2:
                    states.pop(index2)

    if final_states:
        for index1, val1 in enumerate(final_states):
            for index2, val2 in enumerate(final_states):
                if index2 <= index1:
                    continue
                elif val1 == val2:
                    final_states.pop(index2)
    if final_states:
        for index1, val1 in enumerate(final_states):
            for index2, val2 in enumerate(final_states):
                if index2 <= index1:
                    continue
                elif val1 == val2:
                    states.pop(index2)

    #alphabet
    if alphabets:
        for index1, val1 in enumerate(alphabets):
            for index2, val2 in enumerate(alphabets):
                if index2 <= index1:
                    continue
                elif val1 == val2:
                    alphabets.pop(index2)
    if alphabets:
        for index1, val1 in enumerate(alphabets):
            for index2, val2 in enumerate(alphabets):
                if index2 <= index1:
                    continue
                elif val1 == val2:
                    alphabets.pop(index2)

    #rules[count_rules]
    if rules:
        for index1, val1 in enumerate(rules):
            for index2, val2 in enumerate(rules):
                if index2 <= index1:
                    continue
                elif set(val1) == set(val2):
                    rules.pop(index2)
    if rules:
        for index1, val1 in enumerate(rules):
            for index2, val2 in enumerate(rules):
                if index2 <= index1:
                    continue
                elif set(val1) == set(val2):
                    rules.pop(index2)

    #check semantic
    #empty alphabet
    if not alphabets:
        programExit(input_file,output_file, 41)
    
    #check rules
    if rules:
        for index1, list_with_rule in enumerate(rules):
            if not ( (list_with_rule[0] in states) and (list_with_rule[1] in alphabets or list_with_rule[1]=="''" ) and (list_with_rule[2] in states) ):
                programExit(input_file,output_file, 41)

    #starting state
    if not start_state:
        programExit(input_file,output_file, 41)
    if not start_state[0] in states:
        programExit(input_file,output_file, 41)
    
    #final states
    if final_states:
        for index, fstate in enumerate(final_states):
            if not fstate in states:
                programExit(input_file,output_file, 41)
    
    if (d_flag or e_flag):
        #EPSILON
        #create epsilon closure for each state
        epsilon = []
        for index, value in enumerate(states):
            epsilon.append([])
            epsilon[index].append(value)
    
        #create closures
        for index, Q in enumerate(epsilon):
            while True:
                check_list = list(Q)
                for i, element in enumerate(Q):
                    #check every state, if is on lest side and char is ''
                    if rules:
                        for j, list_with_rule in enumerate(rules):
                            if (list_with_rule[0] == element ) and (list_with_rule[1] == "''") :
                                if not list_with_rule[2] in Q:
                                    Q.append(list_with_rule[2])
                #check if list changed
                if set(Q) == set (check_list):
                    break
    
        #add final states
        for index, Q in enumerate(epsilon):
            for i, element in enumerate(Q):
                if element in final_states:
                    if not Q[0] in final_states:
                        final_states.append(Q[0])
    
        #create epsilon free rules
        new_rules = []
    
        for index, state_value in enumerate(states):
    
            #add rules without epsilon
            #read first state in epsilon closure
            P=epsilon[index].pop(0)
    
            #add echach non epsilon state
            if rules:
                for j, list_with_rule in enumerate(rules):
                    if (list_with_rule[0] == P ) and (list_with_rule[1] != "''") :
                        new_rules.append(list_with_rule)
    
            #check others
            while True:
                if epsilon[index]:
                    element=epsilon[index].pop(0)
                    for j, list_with_rule in enumerate(rules):
                        if (list_with_rule[0] == element ) and (list_with_rule[1] != "''") :
                            l=[P,list_with_rule[1],list_with_rule[2]]
                            new_rules.append(l)
                else:
                    break
        rules=new_rules

    #DETERMINIATION
    #pprint.pprint(locals())

    #Qnew= start state
    #while Qnew do
    #   read states, read all rules
    #   for echar rule set target states
    #   check if target tstates are not allready in Q 
    ##  if not add, check all target states for final states, if yes then  set flag 
    ##  add new target states to Q new, actualize Q
    ## 
    ## go throught list, sort states,create name and add to rules

    if d_flag and rules:

        #create final rules list Q
        #Q= [  [rule1], [rule2]...]
        Q = []
        #create New state list
        Qnext = []

        #create new rule
        #New_rule= [[states],[rule],[states]]
        New_rule = []
        From = []

        Qnext.append(start_state)
        
        while Qnext:
            #print ("Qnext")
            #pprint.pprint(Qnext)
            #print ("Q")
            #pprint.pprint(Q)
            Qnew = list(Qnext)
            del Qnext[:]
            for index_Qnew, value_Qnew in enumerate(Qnew):
                From_list = sorted(value_Qnew)
                Rules_list = []

                #get all alphabets that apply on states from From_list
                for index_state, value_state in enumerate(From_list):
                    for index1, list_with_rule in enumerate(rules):
                        if (list_with_rule[0] == value_state) and  (list_with_rule[1] not in Rules_list):
                            Rules_list.append(list_with_rule[1])
                #print ("Rules_list")
                #pprint.pprint(Rules_list)
    
                #define target states after applying alphabet
                for index_rule, value_rule in enumerate(Rules_list):
                    To_list = []
                    for index1, list_with_rule in enumerate(rules):
                        if (list_with_rule[0] in From_list) and (list_with_rule[1] == value_rule) and (list_with_rule[2] not in To_list):
                            To_list.append(list_with_rule[2])

                    #print ("To_list")
                    #pprint.pprint(To_list)
                    #now we have filled to_list
                    #sort
                    To_list=sorted(To_list)
                    #New_rule= [[from states],[rule],[to states]]
                    New_rule = []
                    New_rule.append(From_list)
                    New_rule.append(value_rule)
                    New_rule.append(To_list)

                    #print ("New_rule")
                    #pprint.pprint(New_rule)
                    #print ("Q-PRED pridanim")
                    #pprint.pprint(Q)
                    #add rule to Q
                    if New_rule not in Q:
                        Q.append(list(New_rule))

                    #print ("Q-PO pridani")
                    #pprint.pprint(Q)
    
                    
                    
                    #if to list not in from list of Q or Qnext, add it to Qnext
                    add_state = True
                    for index_Q, value_Q in enumerate(Q):
                        #print (index_Q)
                        if value_Q[0] == New_rule[2]:
                            add_state = False
                    if Qnext:
                        for index_Qnext, value_Qnext in enumerate(Qnext):
                            if value_Qnext == To_list:
                                add_state = False

                    
    
                    #add target state to next iteration
                    if add_state:
                        Qnext.append(To_list)
                    del New_rule[:]
                    
                    #print ("Qnext zatial")
                    #pprint.pprint(Qnext)
        Index_final_states = []
        for index_Q, value_Q in enumerate(Q):
            match = False
            for index_state, value_state in enumerate(value_Q[0]):
                if value_state in final_states:
                    match = True
                    break
            if match:
                Index_final_states.append(index_Q)
        del states[:]
        del final_states[:]

        for index_Q, value_Q in enumerate(Q):
            value_Q[0]='_'.join(value_Q[0])
            #check if states is allready in list
            if value_Q[0] not in states:
                states.append(value_Q[0])
            value_Q[2]='_'.join(value_Q[2])
            if value_Q[2] not in states:
                states.append(value_Q[2])
            #if index of rule is in list, add it to final states
            if index_Q in Index_final_states and value_Q[0] not in final_states:
                final_states.append(value_Q[0])
        rules=Q






    
    








    

    #OUTPUT
    output=""
    output+="(\n"
    #state
    output+="{"
    states=sorted(states )
    for i, print_state in enumerate(states):
        output+=print_state
        output+=", "
    if states:
        output = output[:-2]
    output+="},\n"
    #alphabet
    output+="{"
    alphabets=sorted(alphabets)
    for i, p in enumerate(alphabets):
        output+=p
        output+=", "
    output = output[:-2]
    output+="},\n{\n"
    rules.sort()
    if rules:
        for index1, list_with_rule in enumerate(rules):
            output+=list_with_rule[0]
            output += " "
            output+=list_with_rule[1]
            output += " -> "
            output+=list_with_rule[2]
            output+=",\n"
    if rules:
        output = output[:-2]
        output+="\n"
    output+="},\n"
    output+=start_state[0]
    output+=",\n{"
    final_states=sorted(final_states)
    for i, p in enumerate(final_states):
        output+=p
        output+=", "
    if final_states:
        output = output[:-2]
    output+="}\n)"

    #print out
    output_file.write(output)
    programExit(input_file,output_file, 0)


if __name__ == "__main__":
    main()
