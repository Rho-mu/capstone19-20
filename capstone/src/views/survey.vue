<template>
  <div class="survey">
    <form @submit="submitName">
      <div>
        <img src="../assets/Logo-Black.png"><br>
        <h4>Please Fill out the Survey</h4>
        <input type="text" v-model="newUser.first_Name" placeholder="First Name" required><br>

        <input type="text" v-model="newUser.last_Name" placeholder="Last Name" required><br>

        <input type="text" v-model="newUser.occupation" placeholder="Affiliation (e.g., Tempe State University, Taylor High School)"required><br>

        <input type="text" v-model="newUser.locale" placeholder="City, State, Country"required><br><br>

        <label for="roles">Choose an Affiliation Role:</label><br>
        <select v-model="newUser.role" class="roles" required>
          <option value="Student(K-12)">Student (K-12)</option>
          <option value="Student(Undergraduate)">Student (Undergraduate)</option>
          <option value="Student(Graduate)">Student (Graduate)</option>
          <option value="Instructor(K-12)">Instructor (K-12)</option>
          <option value="Instructor(Undergraduate)">Instructor (Undergraduate)</option>
          <option value="Instructor(graduate-level)">Instructor (Graduate-Level)</option>
          <option value="Researcher(Bachelors or masters)">Researcher (Bachelors or Masters level)</option>
          <option value="Researcher(PhD Level)">Researcher (PhD Level)</option>
          <option value="Natural Resource Manager, Conservationist, or Practitioner">Natural Resource Manager, Conservationist, or Practitioner</option>
          <option value="Other">Other</option>

        </select>
        <br>
        <br>
        <button type="submit" value="Submit">Submit</button>
      </div>
      <div>
        <ul>
          <li v-for="user of users"
            v-bind:key="user['.key']">
          </li>
        </ul>
      </div>
  </form>
  </div>
</template>

<script>
import { userRef } from '../main';

export default {
  name: 'survey',
  data () {
    return {
      newUser: {
        first_Name: '',
        last_Name: '',
        occupation: '',
        local: '',
        role: ''
      }
    }
  },
  firebase: {
    users: userRef
  },
  methods: {
    submitName() {
      var keyRef = userRef.push( this.newUser );
      this.$router.replace('inputs-vis');
    }
  }
}
</script>

<style scoped>
  .survey {
    margin-top: 80px;
  }

  ul {
    list-style-type: none;
    padding: 0;
  }

  li {
    display: inline-block;
    margin: 0 10px;
  }

  button {
    margin-top: 10px;
    background-color: #44c767;
    border-radius: 20px;
    border: none;
    padding: 10px 30px;
    color:#ffffff;
    font-family:Arial;
    font-size: 13px;
    display: inline-block;
  }

  button:hover {
    background-color: #EEE;
    color: black;
  }
  input {
    margin: 10px 0;
    width: 25%;
    padding: 15px;
    border-radius: 10px;
    border-width: thin;
  }

  .roles {
    width: 22%;
  }
</style>
