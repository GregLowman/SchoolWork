// ************************************************
// Section 1 : Dependencies
// ************************************************

// importing the dependencies
// Express is a NodeJS framework that, among other features, allows us to create HTML templates.
const express = require('express');
const bodyParser = require('body-parser');
const pgp = require('pg-promise')();
require('dotenv').config();

// ************************************************
//  Section 2 : Initialization
// ************************************************

// defining the Express app
const app = express();
// using bodyParser to parse JSON in the request body into JS objects
app.use(bodyParser.json());
// Database connection details
const dbConfig = {
  host: 'db',
  port: 5432,
  database: process.env.POSTGRES_DB,
  user: process.env.POSTGRES_USER,
  password: process.env.POSTGRES_PASSWORD,
};
// Connect to database using the above details
const db = pgp(dbConfig);

// ************************************************
//  Section 3 : Part B
// ************************************************

// Endpoint 1 :  GET Endpoint Implementation (Default)
const message = 'Hey there!';
app.get('/', (req, res) => {
  res.send(message);
});

// Endpoint 2 : GET Endpoint Implementation
app.get('/getReviewsByTrailID', async (req, res) => {
  //TODO: Read the trail_id from the client request
  const trail_id = req.query.trail_id;

  //TODO: Write the database query to return the reviews based on trail_id
  const query = "SELECT r.review_id, r.username, r.review, r.rating FROM reviews AS r JOIN trails_to_reviews trr ON r.review_id = trr.review_id WHERE trr.trail_id = $1;";

  //TODO: Make the database request using async/await. Look at the lab for examples. Remember to use try/catch
  try {
    const results = await db.any(query, [trail_id])
    res.status(200).json({data: results})
  }
  catch (err) {
    res.status(400).json({error: err.message})
  }

  //TODO: Return the data to the client

});

// Endpoint 3 : GET Endpoint Implementation 
app.get('/getTop3Trails', async (req, res) => {
  //TODO: Read the location from the client request
  const trail_id = req.query.trail_id;
  const review_id = req.query.review_id;
  const rating = req.query.rating;

  //TODO: Write the database query to return the top 3 trails and filter by location from client request
  const query = "SELECT t.trail_id, t.name, AVG(r.rating) AS avg_rating FROM trails t JOIN trails_to_reviews tr ON tr.trail_id = t.trail_id JOIN reviews r ON r.review_id = tr.review_id GROUP BY t.trail_id, t.name ORDER BY avg_rating DESC LIMIT 3;";
  //TODO: Make the database request using async/await. Look at the lab for examples. Remember to use try/catch

  //TODO: Return the data to the client
    try {
    const results = await db.any(query, [trail_id])
    res.status(200).json({data: results})
  }
  catch (err) {
    res.status(400).json({error: err.message})
  }
});

// ************************************************
//  Section 4 : Part C
// ************************************************

// Endpoint 4 : GET Endpoint Implementation 
app.get('/getTrails', async (req, res) => {
  const name = req.query.name;
  let difficulty = req.query.difficulty;
  const location = req.query.location;
  const values = [];

  let query = "SELECT t.trail_id, t.name, t.difficulty, t.location FROM trails AS t ";
  
  if(difficulty)
  {
    switch(difficulty)
      {
        case "1":
          difficulty = "easy";
          break;
        case "2":
          difficulty = "moderate";
          break;
        case "3":
          difficulty = "difficult";
          break;
        case "4":
          difficulty = "very_difficult";
          break;
      }
      values.push(difficulty);

      query += "WHERE t.difficulty = $1";

      if(location)
      {
        values.push(location);
        query += " AND t.location = $2";
      }
  }

  else if(!difficulty && location)
  {
    values.push(location);
    query += "WHERE t.location = $1";
  }

  try {
    const results = await db.any(query, values)
    res.status(200).json({data: results})
  }
  catch (err) {
    res.status(400).json({error: err.message})
  }
});

// Endpoint 5 : POST Endpoint Implementation
app.post('/addReview', async (req, res) => {
  //TODO: Read the reviews and/or images from the client request

  const username = req.body.username;
  const review = req.body.review;
  const rating = req.body.rating;
  const trail_id = req.body.trail_id;
  const image_url = req.body.image_url;
  const image_caption = req.body.image_caption;

  //TODO: Write the database query to insert the reviews and/or images into the tables. If the client provides image information, you will need to insert data into the reviews_to_images table as well. 

  try {
    const result = await db.task(async t => {
      const reviewResult = await t.one(
        "INSERT INTO reviews (username, review, rating) VALUES ($1, $2, $3) RETURNING review_id;", [username, review, rating]
      );
      await t.none(
        "INSERT INTO trails_to_reviews (trail_id, review_id) VALUES ($1, $2);", [trail_id, reviewResult.review_id]
      );

      if(image_url || image_caption)
      {
        const imageResult = await t.one(
          "INSERT INTO images (image_url, image_caption) VALUES ($1, $2) RETURNING image_id;", [image_url, image_caption]
        );
        await t.none(
          "INSERT INTO reviews_to_images (review_id, image_id) VALUES ($1, $2);", [reviewResult.review_id, imageResult.image_id]
        );
      }
      return reviewResult;
    });

    
    res.status(201).json({message: "Data added successfully", review_id: result.review_id});
  }

  catch (err) {
    res.status(400).json({error: err.message});
  }
});



// ************************************************
//  Section 4 : Extra Credit
// ************************************************

// Endpoint 6 : PUT Endpoint Implementation
app.put('/updateReview', async(req, res) => {
    const review = req.body.review;
    const rating = req.body.rating;
    const trail_id = req.body.trail_id;
    const image_url = req.body.image_url;
    const image_caption = req.body.image_caption;
    const review_id = req.body.review_id;
    const image_id = req.body.image_id;

  try{
    await db.task(async t => {
      
      if(review || rating)
      {
        await t.none("UPDATE reviews SET review = $1, rating = $2 WHERE review_id = $3;", [review, rating, review_id]);
      }
      if(image_caption || image_url)
      {
        await t.none("UPDATE images SET image_caption = $1, image_url = $2 WHERE image_id = $3", [image_caption, image_url, image_id]);
      }
      return;
    });

    if((review || rating) && !(image_caption || image_url)){
      res.status(201).json({message: "Data updated succesfully", review_id : review_id});
    }
    else if((image_caption || image_url) && !(review || rating)){
      res.status(201).json({message: "Data updated succesfully", image_id : image_id});
    }
    else if((image_caption || image_url) && (review || rating)){
      res.status(201).json({message: "Data updated succesfully", review_id : review_id, image_id : image_id});
    }
    else{
      res.status(400).json({message : "Data not updated"});
    }
  }
  catch(err) {
    res.status(400).json({error: err.message});
  }
});

// Endpoint 7 : DELETE Endpoint Implementation
app.delete('/deleteReview', async (req, res) => {
  const review_id = req.body.review_id;
  const username = req.body.username;
  const rating = req.body.rating;
  let trigger = 0

  try{
    await db.task(async t => {

      if(review_id)
      {
        await t.none("DELETE FROM reviews_to_images WHERE review_id = $1", [review_id]);
        await t.none("DELETE FROM reviews WHERE review_id = $1;", [review_id]);
        trigger = 1;
      }
      else if (username)
      {
        const reviews = await t.any("SELECT review_id FROM reviews WHERE username = $1;", [username])
        const ids = reviews.map(r => r.review_id);
        await t.none("DELETE FROM reviews_to_images WHERE review_id = ANY($1);", [ids])
        await t.none("DELETE FROM reviews WHERE username = $1;", [username])
        trigger = 1;
      }
      else if(rating)
      {
        const reviews = await t.any("SELECT review_id FROM reviews WHERE rating = $1;" [rating]);
        const ids = reviews.map(r => r.review_id);
        await t.none("DELETE FROM reviews_to_images WHERE review_id = ANY($1);", [ids])
        await t.none("DELETE FROM reviews WHERE rating = $1", [rating])
        trigger = 1;
      }
      return;
    });

    if(trigger == 1)
    {
      res.status(201).json({message: "Succesfully Deleted"});
    }
    else
    {
      res.status(400).json({message: "No entry deleted"});
    }
  }
  catch(err)
  {
    res.status(400).json({error: err.message});
  }
});

// ************************************************
//  Section 6 : Keeping the server actively listening for client requests
// ************************************************
// starting the server and keeping the connection open to listen for more requests
app.listen(3000, () => {
  console.log('listening on port 3000');
});