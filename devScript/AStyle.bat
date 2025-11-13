cd ../
for /r %%f in (*.cpp;*.h;*.hpp) do astyle.exe -n -A1 --indent=force-tab=4 --indent-after-parens ^
 --indent-namespaces --indent-col1-comments --pad-comma --pad-include --squeeze-lines=1 --squeeze-ws ^
 --keep-one-line-blocks %%f