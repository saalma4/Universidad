package es.taw.julio2025.entity;

import lombok.Data;

import javax.persistence.*;
import java.util.List;

@Entity
@Data
@Table(name = "Habitat")
public class Habitat {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;

    private String nombre;
    private String ubicacion;

    @ManyToMany(mappedBy = "habitats")
    private List<Dinosaurio> dinosaurios;

    @Override
    public String toString() {
        return "Habitat[ id=" + id + " ]";
    }
}