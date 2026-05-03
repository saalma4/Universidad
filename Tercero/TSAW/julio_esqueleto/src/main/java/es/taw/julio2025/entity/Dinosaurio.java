package es.taw.julio2025.entity;

import lombok.Data;

import javax.persistence.*;
import java.util.List;

@Entity
@Data
@Table(name = "Dinosaurio")
public class Dinosaurio {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;

    private String nombre;
    private Float tamaño_metros;
    private Float peso_toneladas;

    @ManyToOne
    @JoinColumn(name = "periodo_id")
    private Periodo periodo;

    @ManyToOne
    @JoinColumn(name = "dieta_id")
    private Dieta dieta;

    @ManyToMany
    @JoinTable(
        name = "Dinosaurio_Habitat",
        joinColumns = @JoinColumn(name = "dinosaurio_id"),
        inverseJoinColumns = @JoinColumn(name = "habitat_id")
    )
    private List<Habitat> habitats;

    @ManyToMany
    @JoinTable(
        name = "Dinosaurio_Descubridor",
        joinColumns = @JoinColumn(name = "dinosaurio_id"),
        inverseJoinColumns = @JoinColumn(name = "descubridor_id")
    )
    private List<Descubridor> descubridores;

    @Override
    public String toString() {
        return "Dinosaurio[ id=" + id + " ]";
    }

    public String getHabitatsString () {
        String str = "";
        if (habitats == null) {
            return "";
        } else {
            for (Habitat habitat: habitats) {
                str += habitat.getNombre() + "(" + habitat.getUbicacion() + ")  ";
            }
        }
        return str;
    }

}