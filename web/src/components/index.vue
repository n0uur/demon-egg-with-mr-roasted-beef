<template>
  <div>
    <div class="block top">
      <img src="/static/logo.png" class="logo-img animated fadeIn delay-1s" draggable="false">
      <img src="/static/egg_beef.png" class="egg-beef-img" draggable="false">
      <h1 class="top-bottom animated delay-2s bounce">
        <i class="fas fa-chevron-down animated fadeIn delay-2s slower"></i>
      </h1>
    </div>
    <div class="block bg-warning">

    </div>
  </div>
</template>

<script>
export default {

};
</script>

<style>

.logo-img {
  position: absolute;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  height: 80vh;
  margin: auto;
  z-index: 1;
}

.egg-beef-img {
  position: absolute;
  bottom: -20px;
  left: 100px;
  transform: scale(2);
  opacity: 0.2;
  z-index: 0;
}

.block {
  height: 100vh;
  widows: 100vw;
  position: relative;
  overflow: hidden;
}

.top-bottom {
  position: absolute;
  bottom: 5vh;
  left: 0;
  right: 0;
  margin: auto;
}

.top {
  background: black;
}

</style>