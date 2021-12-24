r110  = function (a , b , c )
if ((a == 1 )and (b == 1 )and (c == 1 )) then
return 0 
else
if ((a == 1 )and (b == 1 )and (c == 0 )) then
return 1 
else
if ((a == 1 )and (b == 0 )and (c == 1 )) then
return 1 
else
if ((a == 1 )and (b == 0 )and (c == 0 )) then
return 0 
else
if ((a == 0 )and (b == 1 )and (c == 1 )) then
return 1 
else
if ((a == 1 )and (b == 1 )and (c == 0 )) then
return 1 
else
if ((a == 0 )and (b == 0 )and (c == 1 )) then
return 1 
else
if ((a == 0 )and (b == 0 )and (c == 0 )) then
return 0 
else
return 0 
end

end

end

end

end

end

end

end

end

r  = 51 
buff  =  {0 , 1 , 0 , 1 , 1 , 0 , 1 , 1 , 1 , 0 , 1 , 1 , 1 , 1 , 0 , 0 , 1 , 1 , 0 , 1 , 1 , 1 , 0 , 0 , 1 , 0 , 1 , 1 , 0 , 1 , 1 , 0 , 1 , 1 , 1 , 0 , 1 , 1 , 0 , 1 , 0 , 1 , 0 , 1 , 1 , 0 , 1 , 1 , 0 , 1 , 1 } 
prnt_buff  = function (a )
if (buff  [a ] == 1 ) then
io.write ("#" )
else
io.write (" " )
end

if (a == 0 ) then
return 0 
else
return prnt_buff ((a - 1 ))
end

end

prnt_buff (r )print ()dostuff  = function (ss )
cp  =  {} 

next_iter  = function (x )
cp  [x ]  = r110 (buff  [(x - 1 )] , buff  [x ] , buff  [(x + 1 )] )

if (x == (r - 1 )) then
return cp 
else
return next_iter ((x + 1 ))
end

end


buff  = next_iter (1 )

prnt_buff (r )
print ()
if (ss == 0 ) then
return 0 
else
return dostuff ((ss - 1 ))
end

end

dostuff (40 )