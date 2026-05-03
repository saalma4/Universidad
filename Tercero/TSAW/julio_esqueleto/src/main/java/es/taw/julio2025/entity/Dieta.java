package es.taw.julio2025.entity;

import lombok.Data;

import javax.persistence.*;
import java.util.List;

@Entity
@Data
@Table(name = "Dieta")
public class Dieta {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;

    private String tipo;

    @OneToMany(mappedBy = "dieta")
    private List<Dinosaurio> dinosaurios;

    @Override
    public String toString() {
        return "Dieta[ id=" + id + " ]";
    }
}