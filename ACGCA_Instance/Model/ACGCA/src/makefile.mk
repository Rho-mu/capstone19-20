
ACGCA.dll : excessgrowing.c misc_growth_funcs.c putonallometry.c growthloop.c rebuildstaticstate.c shrinkingsize.c Rgrowthloop.c instance.c
	gcc -shared excessgrowing.c misc_growth_funcs.c putonallometry.c growthloop.c rebuildstaticstate.c shrinkingsize.c Rgrowthloop.c instance.c -o ACGCA.dll

clean : 
	rm ACGCA.dll





