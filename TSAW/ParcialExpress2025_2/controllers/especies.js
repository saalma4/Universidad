const initModels = require("../models/init-models");
const sequelize = require("sequelize");
const models = initModels(sequelize);

const controller = {};

controller.editarEspecie = async function (req, res, next) {
    try {

    } catch (error) {
        res.send("Se ha producido un error " + error);
    }
};
controller.guardarEspecie = async function (req, res, next){
    try{

    }catch{

    }
}
module.exports = controller;