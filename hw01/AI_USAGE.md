I utilized Claude for code debugging, logic checking when designing function implementation and for assistance with code development. 

One thing it got wrong was trying to shift a 32 bit int by 32 positions which is undefined behavior. This was found when get_field and set_field tests were failing. The fix was to use 1u instead of 1 and add a special case for when width = 32. 