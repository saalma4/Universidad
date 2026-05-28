const express = require("express");
const router = express.Router();

const planetasController = require("../controllers/planetas")
const especiesController = require("../controllers/especies")

router.get("/", planetasController.listarPlanetas)
router.get("/especies/:id", especiesController.editarEspecie)
router.post("/especies/:id", especiesController.guardarEspecie)

module.exports = router;
