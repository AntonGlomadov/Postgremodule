#include "postgres.h"
#include "fmgr.h"
#include "utils/builtins.h"
#include "funcapi.h"


#ifdef PG_MODULE_MAGIC
PG_MODULE_MAGIC;
#endif

PG_FUNCTION_INFO_V1(superfunction);

Datum superfunction(PG_FUNCTION_ARGS) {
    int32 N = PG_GETARG_INT32(0);
    text *arg = PG_GETARG_TEXT_PP(1);
    char *A = text_to_cstring(arg);
    FuncCallContext *funcctx;
    TupleDesc tupdesc;
    AttInMetadata *attinmeta;
    int i;

    if (SRF_IS_FIRSTCALL()) {
        MemoryContext oldcontext;
        funcctx = SRF_FIRSTCALL_INIT();
        oldcontext = MemoryContextSwitchTo(funcctx->multi_call_memory_ctx);

        tupdesc = CreateTemplateTupleDesc(2); // Исправлено
        TupleDescInitEntry(tupdesc, (AttrNumber) 1, "order", INT4OID, -1, 0);
        TupleDescInitEntry(tupdesc, (AttrNumber) 2, "string", TEXTOID, -1, 0);

        attinmeta = TupleDescGetAttInMetadata(tupdesc);
        funcctx->attinmeta = attinmeta;

        funcctx->user_fctx = (void *) 0;
        MemoryContextSwitchTo(oldcontext);
    }


    funcctx = SRF_PERCALL_SETUP();
    attinmeta = funcctx->attinmeta;

    for (i = funcctx->call_cntr; i < N; i++) {
        Datum values[2];
        bool nulls[2] = {false, false};
        HeapTuple tuple;
        Datum result;
        values[0] = Int32GetDatum(i + 1);
        char *string = palloc(i + 2); // +1 для символа
        memset(string, *A, i + 1);
        string[i + 1] = '\0'; // Завершаем строку нулем

        values[1] = CStringGetTextDatum(string);

        tuple = heap_form_tuple(attinmeta->tupdesc, values, nulls);
        result = HeapTupleGetDatum(tuple);

        SRF_RETURN_NEXT(funcctx, result);
    }
    SRF_RETURN_DONE(funcctx);
}
