633c633,634
< 
---
> typedef void (*R_CFinalizer_t)(SEXP);
> typedef size_t R_size_t;
643a645
> SEXP Rf_allocVectorInPlace(SEXPTYPE, R_xlen_t, void*, void*, R_CFinalizer_t, void*);
703a706
> R_size_t Rf_sizeofHeader(void);
760d762
< typedef void (*R_CFinalizer_t)(SEXP);
937a940
> #define allocVectorInPlace  Rf_allocVectorInPlace
1067a1071
> #define sizeofHeader	Rf_sizeofHeader
