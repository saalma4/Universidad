const initModels = require("../models/init-models");
const sequelize = require("sequelize");
const models = initModels(sequelize);

const controller = {};

// Listar planetas /////////////////////////////////////////////////////////////////////////////////////////////////////
controller.listarPlanetas = async function (req, res, next) {
    try {
        const planetas = await models.Planeta.findAll()
        const especies = await models.Especie.findAll()
        res.render("index", {planetas, especies});
    } catch (error) {
        res.send("Se ha producido un error " + error);
    }
};

controller.listarPlanetasPorDiametro = async function (req, res, next) {
    try {
        const planetas = await models.Planeta.findAll({
            where: {
                diametro: {
                    [sequelize.Op.gt]: req.params.min,
                    [sequelize.Op.lt]: req.params.max
                }
            }
        })
        const especies = await models.Especie.findAll()
        res.render("index", {planetas, especies});
    } catch (error) {
        res.send("Se ha producido un error " + error);
    }
};
module.exports = controller;
