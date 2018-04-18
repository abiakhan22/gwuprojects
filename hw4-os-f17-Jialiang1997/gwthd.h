typedef int     gwthd_t;
typedef void *(*gwthd_fn_t)(void *);

int     gwthd_create(gwthd_t *childid, gwthd_fn_t fn, void *data);
void    gwthd_exit(void);
int     gwthd_join(gwthd_t child);
gwthd_t gwthd_id(void);
