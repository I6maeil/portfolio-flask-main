const express = require("express");
const mongoose = require("mongoose");

const app = express();
const PORT = 3000;

// Middleware باش نقرا JSON
app.use(express.json());

// 1. Connect DB
mongoose.connect("mongodb://127.0.0.1:27017/mydb")
  .then(() => console.log("✅ Connected to MongoDB"))
  .catch(err => console.error(err));

// 2. Création d’un modèle (User)
const User = mongoose.model("User", {
  name: String,
  age: Number
});

// 3. Routes
// Ajouter user
app.post("/users", async (req, res) => {
  const user = new User(req.body);
  await user.save();
  res.json(user);
});

// Afficher tous les users
app.get("/users", async (req, res) => {
  const users = await User.find();
  res.json(users);
});

// 4. Démarrage
app.listen(PORT, () => {
  console.log(`🚀 Server running on http://localhost:${PORT}`);
});
