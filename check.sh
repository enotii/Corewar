#!/bin/bash
rm 1.hex
rm 2.hex
rm jumper.cor
rm change.diff
./asm /Users/kristinazueva/Corewaritems/git/Corewar/champs/jumper.s
chmod 777 /Users/kristinazueva/Corewaritems/git/Corewar/jumper.cor
diff /Users/kristinazueva/Corewaritems/git/Corewar/champs/jumper.cor /Users/kristinazueva/Corewaritems/git/Corewar/jumper.cor >> change.diff
xxd /Users/kristinazueva/Corewaritems/git/Corewar/champs/jumper.cor >> 1.hex
xxd /Users/kristinazueva/Corewaritems/git/Corewar/jumper.cor >> 2.hex
diff 1.hex 2.hex > change.diff