
SIPPDIR=$HOME/.sipp

NAME=$(echo $1 | sed 's/.spp//g')

echo $NAME

echo "#include <$SIPPDIR/sipp.hpp>" > $NAME.cpp
cat $SIPPDIR/utils/startOfCppFile >> $NAME.cpp

# Legger inn masse semikolon, for sikkerhets skyld,
# Prosesserer også Metode-deklarasjoner ved å gjøre
# dem om til lambda-uttrykk.
cat $1 | awk '{print $0 ";"} /\/\//{print ";"}' | sed 's:Metode \([a-Z]*\)(:auto \1 = [\&](:g' >> $NAME.cpp

cat $SIPPDIR/utils/endOfCppFile  >> $NAME.cpp

g++-5 -std=c++14 $NAME.cpp -o $NAME && ./$NAME
