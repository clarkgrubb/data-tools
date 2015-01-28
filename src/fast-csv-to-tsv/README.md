# OVERVIEW

Convert a UTF-8 encoded CSV file to a UTF-8 encoded TSV file.

For a definition of the CSV format we use [RFC 4180](https://tools.ietf.org/html/rfc4180).

For a definition of the tSV format we follow the [IANA](https://www.iana.org/assignments/media-types/text/tab-separated-values).

# FLAGS

-x --strip
-r --replace
-e --escape
-p --pad


-d DELIMTER --delimiter DELIMITER
-q QUOTECHAR --quotechar QUOTECHAR
--header NAME,NAME,...

# STATE MACHINE

<img src="state.png">
