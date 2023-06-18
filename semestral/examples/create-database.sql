DROP TABLE IF EXISTS example1;
DROP TABLE IF EXISTS example2;
DROP TABLE IF EXISTS example3;
DROP TABLE IF EXISTS example4;

CREATE TABLE IF NOT EXISTS example1 (
    name VARCHAR(255) NOT NULL,
    age VARCHAR(255) NOT NULL,
    height VARCHAR(255) NOT NULL
);

CREATE TABLE IF NOT EXISTS example2 (
    name VARCHAR(255) NOT NULL,
    age VARCHAR(255) NOT NULL,
    height VARCHAR(255) NOT NULL
);

CREATE TABLE IF NOT EXISTS example3 (
    school VARCHAR(255) NOT NULL,
    tuition VARCHAR(255) NOT NULL
);

CREATE TABLE IF NOT EXISTS example4 (
    name VARCHAR(255) NOT NULL,
    school VARCHAR(255) NOT NULL
);

INSERT INTO example1 (name, age, height) VALUES ('Mary', '28', '170');
INSERT INTO example1 (name, age, height) VALUES ('John', '25', '180');
INSERT INTO example1 (name, age, height) VALUES ('Alfred', '30', '175');
INSERT INTO example1 (name, age, height) VALUES ('Betty', '20', '165');

INSERT INTO example2 (name, age, height) VALUES ('Octopus', '281', '1170');
INSERT INTO example2 (name, age, height) VALUES ('Betty', '20', '165');
INSERT INTO example2 (name, age, height) VALUES ('Benjamin', '26', '80');
INSERT INTO example2 (name, age, height) VALUES ('Alfred', '30', '175');

INSERT INTO example3 (school, tuition) VALUES ('FIT', '0');
INSERT INTO example3 (school, tuition) VALUES ('FEL', '0');
INSERT INTO example3 (school, tuition) VALUES ('Harvard', '500000');
INSERT INTO example3 (school, tuition) VALUES ('MIT', '100000');

INSERT INTO example4 (name, school) VALUES ('Mary', 'FIT');
INSERT INTO example4 (name, school) VALUES ('John', 'MIT');
INSERT INTO example4 (name, school) VALUES ('Octopus', 'FIT');
INSERT INTO example4 (name, school) VALUES ('Betty', 'FEL');

SELECT * FROM ((SELECT * FROM ((SELECT * FROM example3) AS p19t4xfi87  NATURAL JOIN (SELECT * FROM example4) AS h2wjq9j1rl )) AS kk10ttkv6d  NATURAL JOIN ((SELECT * FROM example2) UNION (SELECT * FROM example1)) AS itgssec8uv )
