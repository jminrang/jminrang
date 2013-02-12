echo + target remote localhost:1234\n
target remote localhost:1234

echo + file kernel\n
file kernel

echo + b k_main\n
b k_main
echo + l\n
l
echo + now go to breakpoint 'main()' by run 'c'\n
