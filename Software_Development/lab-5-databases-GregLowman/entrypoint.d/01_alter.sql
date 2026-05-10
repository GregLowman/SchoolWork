ALTER TABLE movies
ADD CONSTRAINT platform_id FOREIGN KEY (platform_id) REFERENCES platforms (id);

--ALTER TABLE