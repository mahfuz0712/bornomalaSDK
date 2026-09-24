#include <bos.h>
#include <window.h>

int mmr_main(){

BOS_Window* w=

bos_window_create(

900,

600,

"New App"

);

bos_window_show(w);

return 0;

}