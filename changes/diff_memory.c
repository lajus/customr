987a988,991
> #define PERSISTENT_MASK 128
> #define PERSISTENT(x) ((x)->sxpinfo.gp & PERSISTENT_MASK)
> #define SET_PERSISTENT(x) ((x)->sxpinfo.gp |= PERSISTENT_MASK)
> 
992a997
> 
1005d1009
< 			R_LargeVallocSize -= size;
1006a1011,1014
> 
> 			if(!PERSISTENT(s)) {
> 				R_LargeVallocSize -= size;
> 
1008,1011c1016,1019
< 			if (IS_LONG_VEC(s))
< 				free(((char *) s) - sizeof(R_long_vec_hdr_t));
< 			else
< 				free(s);
---
> 				if (IS_LONG_VEC(s))
> 					free(((char *) s) - sizeof(R_long_vec_hdr_t));
> 				else
> 					free(s);
1013c1021
< 			free(s);
---
> 				free(s);
1014a1023
> 			}
2552a2562,2607
> 	return s;
> }
> 
> R_size_t sizeofHeader()
> {
> 	return sizeof(SEXPREC_ALIGN);
> }
> 
> // The default finalizer just free blockstart
> static void defaultFinalizer(SEXP x)
> {
> 	if(TYPEOF(x) == EXTPTRSXP)
> 		free(EXTPTR_PTR(x));
> }
> 
> SEXP allocVectorInPlace(SEXPTYPE type, R_xlen_t length, void *dataptr, void *blockstart, R_CFinalizer_t finalizer, void *finalizerArg)
> {
> 	SEXP bs, s = (SEXP)(dataptr - sizeof(SEXPREC_ALIGN));
> 
> 	if(blockstart > dataptr - sizeof(SEXPREC_ALIGN))
> 		return NULL;
> 	if(finalizer == NULL)
> 		finalizer = &defaultFinalizer;
> 	if(finalizerArg == NULL)
> 		finalizerArg = blockstart;
> 
> 	PROTECT(s);
> 	s->sxpinfo = UnmarkedNodeTemplate.sxpinfo;
> 	SETLEVELS(s, 0);
> 	SET_NODE_CLASS(s, LARGE_NODE_CLASS);
> 	//R_LargeVallocSize += size;
> 	R_GenHeap[LARGE_NODE_CLASS].AllocCount++;
> 	R_NodesInUse++;
> 	SNAP_NODE(s, R_GenHeap[LARGE_NODE_CLASS].New);
> 
> 	SETLENGTH(s, length);
> 	ATTRIB(s) = R_NilValue;
> 	TYPEOF(s) = type;
> 	NAMED(s) = 0;
> 	SET_PERSISTENT(s);
> 
> 	// We create an EXTPTRSXP associated with the pointer blockstart, argument for the finalizer and bound to s for the gc
> 	bs = PROTECT(R_MakeExternalPtr(finalizerArg, R_NilValue, R_NilValue));
> 	setAttrib(s, R_InPlaceVectorSymbol, bs);
> 	R_RegisterCFinalizerEx(bs, finalizer, TRUE);
> 	UNPROTECT(2);
