const initModels = require("../models/init-models");
const sequelize = require("sequelize");
const models = initModels(sequelize);

const controller = {};

controller.editarEspecie = async function (req, res, next) {
    try {
    const especie = await models.Especie.findOne({
        where:{
            especie_id : req.params.id
        }
    })
        const familias = await models.Familia_Especie.findAll()
        const personajes_de_especie = await models.Personaje.findAll({
            where:{
                especie: req.params.id
            }
        })
        res.render("especie", {especie, familias, personajes_de_especie})
    } catch (error) {
        res.send("Se ha producido un error " + error);
    }
};
controller.guardarEspecie = async function (req, res, next){
    try{
        if(typeof req.body.especie_id != "undefined"){
            const especie = await models.Especie.findOne({
                where:{
                    especie_id: req.body.especie_id
                }
            })
            if(especie){
                await especie.update({
                    clasificacion: req.body.familia,
                    peso_medio: req.body.peso_medio,
                    esperanza_vida: req.body.esperanza_vida
                })
            }
        }
        res.redirect('/')
    }catch(error){
        res.send("Se ha producido un error " + error);
    }
}
module.exports = controller;
