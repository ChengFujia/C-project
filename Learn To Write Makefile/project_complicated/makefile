# describtion: makefile of complicated project
# version: v1.7
# change log:
# 1.Add comments... v1.1
# 2.Use value change method.. v1.2
# 3.Static modern... v1.3
# 4.Add clean command... v1.4
# 5.Fake target... v1.5
# 6.Add wildcard... v1.6
# 7.Add auto rule depends... v1.7

executbale := complicated
sources := $(wildcard *.c)
objects := $(sources:.c=.o)
deps := $(sources:.c=.d)
CC := gcc
RM := rm -rf

# final target
$(executbale):$(objects)
	$(CC) -o $@ $^

# sub rule1
#main.o:main.c
#	$(CC) -o $@ -c $<

# sub rule2
#complicated.o:complicated.c
#	$(CC) -o $@ -c $<

# v1.3
$(objects):%.o:%.c
	$(CC) -o $@ -c $<

# v1.4
# v1.5 
.PHONY: clean
clean:
	$(RM) $(executbale) $(objects)

# v1.7
sinclude $(deps)
$(deps):%.d:%.change	
	$(CC) -MM $< > $@

