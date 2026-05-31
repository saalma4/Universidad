const express = require("express");
const router = express.Router();

const peliculasController = require('../controllers/peliculas');

router.get("/", peliculasController.listarPeliculas);
router.get("/frases/:id", peliculasController.listarFrases);

module.exports = router;
