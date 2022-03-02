

// Database Paths
var dataIntPathIda = 'autos/ida';
var dataIntPathVuelta = 'autos/vuelta';

var Enero = 'Enero/autos/ida';
var Febrero = 'Febrero/autos/ida';
var Marzo = 'Marzo/autos/ida';
var Abril= 'Abril/autos/ida';
var Mayo = 'Mayo/autos/ida';
var Junio = 'Junio/autos/ida';
var Julio = 'Julio/autos/ida';
var Agosto = 'Agosto/autos/ida';
var Septiembre = 'Septiembre/autos/ida';
var Octubre = 'Octubre/autos/ida';
var Noviembre = 'Noviembre/autos/ida';
var Diciembre = 'Diciembre/autos/ida';

var Enero1 = 'Enero/autos/vuelta';
var Febrero1 = 'Febrero/autos/vuelta';
var Marzo1 = 'Marzo/autos/vuelta';
var Abril1 = 'Abril/autos/vuelta';
var Mayo1 = 'Mayo/autos/vuelta';
var Junio1 = 'Junio/autos/vuelta';
var Julio1 = 'Julio/autos/vuelta';
var Agosto1 = 'Agosto/autos/vuelta';
var Septiembre1 = 'Septiembre/autos/vuelta';
var Octubre1 = 'Octubre/autos/vuelta';
var Noviembre1 = 'Noviembre/autos/vuelta';
var Diciembre1 = 'Diciembre/autos/vuelta';


// Get a database reference 
const databaseInt1 = database.ref(dataIntPathIda);
const databaseInt = database.ref(dataIntPathVuelta);

const dbEnero = database.ref(Enero);
const dbFebrero = database.ref(Febrero);
const dbMarzo = database.ref(Marzo);
const dbAbril = database.ref(Abril);
const dbMayo = database.ref(Mayo);
const dbJunio = database.ref(Junio);
const dbJulio = database.ref(Julio);
const dbAgosto = database.ref(Agosto);
const dbSeptiembre = database.ref(Septiembre);
const dbOctubre = database.ref(Octubre);
const dbNoviembre = database.ref(Noviembre);
const dbDiciembre = database.ref(Diciembre);

const dbEnero1 = database.ref(Enero1);
const dbFebrero1 = database.ref(Febrero1);
const dbMarzo1 = database.ref(Marzo1);
const dbAbril1 = database.ref(Abril1);
const dbMayo1 = database.ref(Mayo1);
const dbJunio1 = database.ref(Junio1);
const dbJulio1 = database.ref(Julio1);
const dbAgosto1 = database.ref(Agosto1);
const dbSeptiembre1 = database.ref(Septiembre1);
const dbOctubre1 = database.ref(Octubre1);
const dbNoviembre1 = database.ref(Noviembre1);
const dbDiciembre1 = database.ref(Diciembre1);


// Variables to save database current values
var indReadingIda;
var intReadingVuelta;

var readingEnero;
var readingFebrero;
var readingMarzo;
var readingAbril;
var readingMayo;
var readingJunio;
var readingJulio;
var readingAgosto;
var readingSeptiembre;
var readingOctubre;
var readingNoviembre;
var readingDiciembre;

var readingEnero1;
var readingFebrero1;
var readingMarzo1;
var readingAbril1;
var readingMayo1;
var readingJunio1;
var readingJulio1;
var readingAgosto1;
var readingSeptiembre1;
var readingOctubre1;
var readingNoviembre1;
var readingDiciembre1;


// Attach an asynchronous callback to read the data
databaseInt1.on('value', (snapshot) => {
  indReadingIda = snapshot.val();
  console.log(indReadingIda);
  document.getElementById("CarroIda").innerHTML = indReadingIda;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

databaseInt.on('value', (snapshot) => {
  intReadingVuelta = snapshot.val();
  console.log(intReadingVuelta);
  document.getElementById("CarroVuelta").innerHTML = intReadingVuelta;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});


dbEnero.on('value', (snapshot) => {
  readingEnero = snapshot.val();
  console.log(readingEnero);
  document.getElementById("EneroIda").innerHTML = readingEnero;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

dbFebrero.on('value', (snapshot) => {
  readingFebrero = snapshot.val();
  console.log(readingFebrero);
  document.getElementById("FebreroIda").innerHTML = readingFebrero;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

dbMarzo.on('value', (snapshot) => {
  readingMarzo = snapshot.val();
  console.log(readingMarzo);
  document.getElementById("MarzoIda").innerHTML = readingMarzo;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

dbAbril.on('value', (snapshot) => {
  readingAbril = snapshot.val();
  console.log(readingAbril);
  document.getElementById("AbrilIda").innerHTML = readingAbril;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

dbMayo.on('value', (snapshot) => {
  readingMayo = snapshot.val();
  console.log(readingMayo);
  document.getElementById("MayoIda").innerHTML = readingMayo;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

dbJunio.on('value', (snapshot) => {
  readingJunio = snapshot.val();
  console.log(readingJunio);
  document.getElementById("JunioIda").innerHTML = readingJunio;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

dbJulio.on('value', (snapshot) => {
  readingJulio = snapshot.val();
  console.log(readingJulio);
  document.getElementById("JulioIda").innerHTML = readingJulio;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

dbAgosto.on('value', (snapshot) => {
  readingAgosto = snapshot.val();
  console.log(readingAgosto);
  document.getElementById("AgostoIda").innerHTML = readingAgosto;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

dbSeptiembre.on('value', (snapshot) => {
  readingSeptiembre = snapshot.val();
  console.log(readingSeptiembre);
  document.getElementById("SeptiembreIda").innerHTML = readingSeptiembre;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

dbOctubre.on('value', (snapshot) => {
  readingOctubre = snapshot.val();
  console.log(readingOctubre);
  document.getElementById("OctubreIda").innerHTML = readingOctubre;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

dbNoviembre.on('value', (snapshot) => {
  readingNoviembre = snapshot.val();
  console.log(readingAgosto);
  document.getElementById("NoviembreIda").innerHTML = readingNoviembre;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

dbDiciembre.on('value', (snapshot) => {
  readingDiciembre = snapshot.val();
  console.log(readingDiciembre);
  document.getElementById("DiciembreIda").innerHTML = readingDiciembre;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});




dbEnero1.on('value', (snapshot) => {
  readingEnero1 = snapshot.val();
  console.log(readingEnero1);
  document.getElementById("EneroVuelta").innerHTML = readingEnero1;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

dbFebrero1.on('value', (snapshot) => {
  readingFebrero1 = snapshot.val();
  console.log(readingFebrero1);
  document.getElementById("FebreroVuelta").innerHTML = readingFebrero1;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

dbMarzo1.on('value', (snapshot) => {
  readingMarzo1 = snapshot.val();
  console.log(readingMarzo1);
  document.getElementById("MarzoVuelta").innerHTML = readingMarzo1;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

dbAbril1.on('value', (snapshot) => {
  readingAbril1 = snapshot.val();
  console.log(readingAbril1);
  document.getElementById("AbrilVuelta").innerHTML = readingAbril1;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

dbMayo1.on('value', (snapshot) => {
  readingMayo1 = snapshot.val();
  console.log(readingMayo1);
  document.getElementById("MayoVuelta").innerHTML = readingMayo1;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

dbJunio1.on('value', (snapshot) => {
  readingJunio1 = snapshot.val();
  console.log(readingJunio1);
  document.getElementById("JunioVuelta").innerHTML = readingJunio1;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

dbJulio1.on('value', (snapshot) => {
  readingJulio1 = snapshot.val();
  console.log(readingJulio1);
  document.getElementById("JulioVuelta").innerHTML = readingJulio1;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

dbAgosto1.on('value', (snapshot) => {
  readingAgosto1 = snapshot.val();
  console.log(readingAgosto1);
  document.getElementById("AgostoVuelta").innerHTML = readingAgosto1;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

dbSeptiembre1.on('value', (snapshot) => {
  readingSeptiembre1 = snapshot.val();
  console.log(readingSeptiembre1);
  document.getElementById("SeptiembreVuelta").innerHTML = readingSeptiembre1;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

dbOctubre1.on('value', (snapshot) => {
  readingOctubre1 = snapshot.val();
  console.log(readingOctubre1);
  document.getElementById("OctubreVuelta").innerHTML = readingOctubre1;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

dbNoviembre1.on('value', (snapshot) => {
  readingNoviembre1 = snapshot.val();
  console.log(readingAgosto1);
  document.getElementById("NoviembreVuelta").innerHTML = readingNoviembre1;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});

dbDiciembre1.on('value', (snapshot) => {
  readingDiciembre1 = snapshot.val();
  console.log(readingDiciembre1);
  document.getElementById("DiciembreVuelta").innerHTML = readingDiciembre1;
}, (errorObject) => {
  console.log('The read failed: ' + errorObject.name);
});