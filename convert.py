out = open('c_retail.dat', 'w')
# out.write('hi there\n')

i = 1 
with open('retail.dat') as f:
    for line in f:
    	outline = str(i)+" "+str(len(line.split(' ')) - 1)+" "+line
    	outline = outline.replace(' ','	')
    	out.write(outline)
    	i += 1
