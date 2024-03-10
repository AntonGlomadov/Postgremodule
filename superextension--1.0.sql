CREATE OR REPLACE FUNCTION superfunction(N integer, A character)
    RETURNS TABLE(ordinal integer, string text)     
    AS 'MODULE_PATHNAME'
    LANGUAGE C;
