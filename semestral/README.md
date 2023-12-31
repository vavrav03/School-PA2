Relational algebra interpreter
==============================================================================================
This project aims to create an interpreter for relation algebra expression. Main source of data are CSV / JSON files. Additionally, SQL conversion capabilities are implemented
==============================================================================================
Features of the project:
- read CSV / JSON file and store it in memory as a variable
- write a variable to a CSV / JSON file
- evaluate relational algebra expressions on variables containing relational data
- convert relational algebra expressions to SQL
- Supported relational algebra operations:
  - set-set operations: union "∪", intersect "∩", except "\", cross "×"
  - set-boolean operations: is_subset "⊆", equals "=", is_proper_subset "⊂"
  - general joins: join "[rel1.col1 < rel2.col3]", left_semi_join "<[condition]", right_semi_join "[condition]>", left_anti_join "!<[condition]", right_anti_join "![condition]>"
  - natural joins (same order as general joins): "*", "<*", "*>", "!<*", "!*>"
  - boolean operations: and "∧", or "∨", not "'", xor "⊕", implies "⇒", equivalent "⇔", nand "↓", nor "↑"
  - projection: project "relation[col1, col3]"
  - selection: select "(condition)"
  - rename: rename "relation[col1 -> new_col1, col3 -> new_col3]"
- efficient memory representation of data - read files only when necessary and only the parts that are needed
- one data type all data - string
- nested expressions using () - Shunting-Yard algorithm
==============================================================================================
Example of usage:
animals1 = "animals1.csv"
animals2 = "animals2.csv"
nourishment = "nourishment.csv"
temp = {{animals1 ∪ animals2} × nourishment}
print temp
sequelize temp
export temp to "temp.csv"
==============================================================================================
How polymorphism is used:
- representation of relational data sources: table in CSV file, JSON data source, expressions - union, intersection, joins
  - all of them implement same interface and we can therefore read record by record from them
  - this enables memory-efficient representation of data sources - we read only the parts of data that are needed
  - this also enables recursive evaluation of relational algebra expressions
  - on top of that, we can easily convert nested expression to SQL using this pattern
- boolean operations - and, or, not, primary boolean expressions
  - all of them implement same interface - this allows to recursively evaluate boolean expressions and convert them to SQL
- export formats: CSV, JSON, XML, PostgresSQL, ...
  - user is going to choose the format through GUI.
  - correct exporter is chosen by expression parser using extension name. Same methods are always present on the exporter,
    therefore, GUI does not have to worry about the format of the exported data
- abstract user interface - unified starting method and configuration based on CLI arguments parsed in main method.
  - this is going to be chosen on start of the app using CLI arguments
  - .run method is going to be called on a common interface from main method. This will start the user interface that has been chosen by the user