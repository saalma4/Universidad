const url = "https://pokeapi.co/api/v2/pokemon/pikachu";

const getPokemonName = async () => {
    const res = await fetch(url);
    const resdeverdad = await res.json();
    console.log(resdeverdad);
};

getPokemonName();