foo1 = $(bar)
foo2 := $(bar)
bar = $(ugh)
ugh = Huh?

all: test1 test2
	echo "foo1 is $(foo1),foo2 is $(foo2)"

bar1 = fooo1
bar1 += fooo2
test1:
	echo $(bar1)

bar2 = fooo1
bar2 ?= fooo2
bar3 ?= fooo2

test2:
	echo "bar2 is $(bar2),bar3 is $(bar3)"


